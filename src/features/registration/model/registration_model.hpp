#pragma once

#include "registration_error.hpp"
#include "registration_result.hpp"
#include "../../../services/matrix/requests/request_manager.hpp"
#include "../../../core/future/future.hpp"

#include <expected>
#include <memory>
#include <string>

namespace epsilon::features::registration {

class RegistrationModel {
    using RequestManager = services::matrix::requests::RequestManager;
    template<typename T>
    using Future = epsilon::core::future::Future<T>;
    using Result = std::expected<RegistrationResult, RegistrationError>;

    std::shared_ptr<RequestManager> m_RequestManager;

public:
    explicit RegistrationModel(std::shared_ptr<RequestManager> request_manager);

    std::shared_ptr<Future<Result>::Handle> Register(const std::string &username, const std::string &password);

    std::shared_ptr<RequestManager> GetRequestManager();
};

}