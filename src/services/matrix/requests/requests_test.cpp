#include <expected>
#include <functional>
#include <gtest/gtest.h>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "authenticated_request_manager.hpp"
#include "iraw_request_manager.hpp"
#include "raw_reply.hpp"
#include "raw_request.hpp"
#include "request.hpp"
#include "request_manager.hpp"

#include "../../serialization/deserializable.hpp"
#include "../../serialization/deserializer.hpp"
#include "../../serialization/iserializable.hpp"
#include "../../serialization/serialization_primitive.hpp"
#include "../../serialization/serializer.hpp"

using namespace epsilon::services::matrix::requests;
using namespace epsilon::services::matrix::serialization;

struct PipelineTestBody : public ISerializable {
    std::string test_value;

    explicit PipelineTestBody(std::string val) : test_value(std::move(val)) {}

  protected:
    SerializationPrimitive GetPrimitiveRepresentation() const override {
        return String{test_value};
    }
};

struct PipelineTestSuccess {
    std::string mock_result_data;
};

struct PipelineTestError {
    std::string mock_error_code;
};

namespace epsilon::services::matrix::serialization {

template <>
::PipelineTestSuccess
Deserialize<::PipelineTestSuccess>(SerializationPrimitive primitive) {
    if (std::holds_alternative<String>(primitive)) {
        return ::PipelineTestSuccess{std::get<String>(primitive).value};
    }
    return ::PipelineTestSuccess{"stub_fallback_success"};
}

template <>
::PipelineTestError
Deserialize<::PipelineTestError>(SerializationPrimitive primitive) {
    if (std::holds_alternative<String>(primitive)) {
        return ::PipelineTestError{std::get<String>(primitive).value};
    }
    return ::PipelineTestError{"stub_fallback_error"};
}

} // namespace epsilon::services::matrix::serialization

class StubSerializationStrategy : public ISerializationStrategy,
                                  public IDeserializationStrategy {
  public:
    std::string Serialize(SerializationPrimitive primitive) const override {
        if (std::holds_alternative<String>(primitive)) {
            return std::get<String>(primitive).value;
        }
        return "raw_stubbed_payload";
    }

    SerializationPrimitive
    Deserialize(const std::string &serialized) const override {
        return String{serialized};
    }
};

class ArchitecturalTestRequest
    : public Request<PipelineTestBody, PipelineTestSuccess, PipelineTestError> {
  public:
    HttpMethod Method() const override { return HttpMethod::PUT; }
    std::string Endpoint() const override { return "matrix/client/r0/sync"; }
};

class StatefulRawRequestManager : public IRawRequestManager {
  public:
    bool execute_called = false;
    RawRequest intercepted_request;
    std::function<void(RawReply)> captured_callback = nullptr;

    void Execute(RawRequest &&request,
                 std::function<void(RawReply)> callback) override {
        execute_called = true;
        intercepted_request = std::move(request);
        captured_callback = callback;
    }
};

class RequestManagerStatefulTest : public ::testing::Test {
  protected:
    std::string test_base_url = "https://matrix.org";
    StatefulRawRequestManager *raw_mgr_ptr = nullptr;
    std::unique_ptr<RequestManager> manager;

    void SetUp() override {
        auto raw_mgr = std::make_unique<StatefulRawRequestManager>();
        raw_mgr_ptr = raw_mgr.get();

        auto serializer_strategy =
            std::make_unique<StubSerializationStrategy>();
        auto deserializer_strategy =
            std::make_unique<StubSerializationStrategy>();

        auto stub_serializer =
            std::make_unique<Serializer>(std::move(serializer_strategy));
        auto stub_deserializer =
            std::make_shared<Deserializer>(std::move(deserializer_strategy));

        manager = std::make_unique<RequestManager>(
            test_base_url, std::move(raw_mgr), std::move(stub_serializer),
            std::move(stub_deserializer));
    }

    void TearDown() override { manager.reset(); }
};

TEST_F(RequestManagerStatefulTest,
       ProperlyAssemblesAndRoutesRawRequestProperties) {
    ArchitecturalTestRequest request;
    request.SetBody(PipelineTestBody{"sync_token_alpha"});

    bool pipeline_callback_executed = false;

    manager->Execute<PipelineTestBody, PipelineTestSuccess, PipelineTestError>(
        request,
        [&pipeline_callback_executed](
            std::optional<
                RequestManager::Reply<PipelineTestSuccess, PipelineTestError>>
                reply) {
            pipeline_callback_executed = true;
            ASSERT_TRUE(reply.has_value());
            EXPECT_EQ(reply->StatusCode, 200);
            ASSERT_TRUE(reply->Body.has_value());
            EXPECT_EQ(reply->Body.value().mock_result_data,
                      "successful_network_stream");
        });

    EXPECT_TRUE(raw_mgr_ptr->execute_called);
    EXPECT_EQ(raw_mgr_ptr->intercepted_request.Method, HttpMethod::PUT);
    EXPECT_EQ(raw_mgr_ptr->intercepted_request.Url,
              "https://matrix.org/matrix/client/r0/sync");
    EXPECT_EQ(raw_mgr_ptr->intercepted_request.Body.value_or(""),
              "sync_token_alpha");

    ASSERT_TRUE(raw_mgr_ptr->captured_callback != nullptr);
    RawReply reply;
    reply.StatusCode = 200;
    reply.Body = "successful_network_stream";
    raw_mgr_ptr->captured_callback(reply);

    EXPECT_TRUE(pipeline_callback_executed);
}

TEST_F(RequestManagerStatefulTest,
       CorrectlyHandlesErrorStatusAndMapsExpectedVariant) {
    ArchitecturalTestRequest request;
    bool pipeline_callback_executed = false;

    manager->Execute<PipelineTestBody, PipelineTestSuccess, PipelineTestError>(
        request,
        [&pipeline_callback_executed](
            std::optional<
                RequestManager::Reply<PipelineTestSuccess, PipelineTestError>>
                reply) {
            pipeline_callback_executed = true;
            ASSERT_TRUE(reply.has_value());
            EXPECT_EQ(reply->StatusCode, 500);
            ASSERT_FALSE(reply->Body.has_value());
            EXPECT_EQ(reply->Body.error().mock_error_code,
                      "internal_server_error_token");
        });

    EXPECT_TRUE(raw_mgr_ptr->execute_called);

    ASSERT_TRUE(raw_mgr_ptr->captured_callback != nullptr);
    RawReply reply;
    reply.StatusCode = 500;
    reply.Body = "internal_server_error_token";
    raw_mgr_ptr->captured_callback(reply);

    EXPECT_TRUE(pipeline_callback_executed);
}

TEST_F(RequestManagerStatefulTest,
       AuthenticatedProxyPipelineAppendsBearerToken) {
    std::string access_token = "OAUTH_BEARER_SECRET_456";

    AuthenticatedRequestManager auth_manager(std::move(manager), access_token);

    ArchitecturalTestRequest request;
    bool pipeline_callback_executed = false;

    auth_manager.Execute<PipelineTestBody, PipelineTestSuccess,
                         PipelineTestError>(
        request,
        [&pipeline_callback_executed](
            std::optional<
                RequestManager::Reply<PipelineTestSuccess, PipelineTestError>>
                reply) {
            pipeline_callback_executed = true;
            ASSERT_TRUE(reply.has_value());
            EXPECT_EQ(reply->StatusCode, 200);
            ASSERT_TRUE(reply->Body.has_value());
            EXPECT_EQ(reply->Body.value().mock_result_data,
                      "authenticated_data_stream");
        });

    EXPECT_TRUE(raw_mgr_ptr->execute_called);
    EXPECT_TRUE(
        raw_mgr_ptr->intercepted_request.Headers.contains("Authorization"));
    EXPECT_EQ(raw_mgr_ptr->intercepted_request.Headers["Authorization"],
              "Bearer OAUTH_BEARER_SECRET_456");

    ASSERT_TRUE(raw_mgr_ptr->captured_callback != nullptr);
    RawReply reply;
    reply.StatusCode = 200;
    reply.Body = "authenticated_data_stream";
    raw_mgr_ptr->captured_callback(reply);

    EXPECT_TRUE(pipeline_callback_executed);
}