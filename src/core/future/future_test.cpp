#include <functional>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <utility>

#include "future.hpp"

using namespace epsilon::core::future;

TEST(FutureTest, InvokesCallbackWhenRealizedAsynchronously) {
    Future<std::string> string_future;
    auto handle = string_future.GetHandle();

    bool callback_executed = false;
    std::string received_value = "";

    handle->Then([&callback_executed, &received_value](const std::string& val) {
        callback_executed = true;
        received_value = val;
    });

    EXPECT_FALSE(callback_executed);

    string_future.Realize("resolved_async_data");

    EXPECT_TRUE(callback_executed);
    EXPECT_EQ(received_value, "resolved_async_data");
}

TEST(FutureTest, InvokesCallbackImmediatelyIfAlreadyRealized) {
    Future<int> int_future;

    int_future.Realize(42);

    auto handle = int_future.GetHandle();

    bool callback_executed = false;
    int received_value = 0;

    handle->Then([&callback_executed, &received_value](const int& val) {
        callback_executed = true;
        received_value = val;
    });

    EXPECT_TRUE(callback_executed);
    EXPECT_EQ(received_value, 42);
}

TEST(FutureTest, SupportsMultipleIndependentObservers) {
    Future<double> double_future;

    auto handle_alpha = double_future.GetHandle();
    auto handle_beta = double_future.GetHandle();

    int activation_count = 0;

    handle_alpha->Then([&activation_count](const double&) { activation_count++; });
    handle_beta->Then([&activation_count](const double&) { activation_count++; });

    EXPECT_EQ(activation_count, 0);

    double_future.Realize(3.14159);

    EXPECT_EQ(activation_count, 2);
}

TEST(FutureTest, ThrowsExceptionWhenRealizedMoreThanOnce) {
    Future<int> critical_future;

    EXPECT_NO_THROW(critical_future.Realize(100));

    EXPECT_THROW(critical_future.Realize(200), std::runtime_error);
}