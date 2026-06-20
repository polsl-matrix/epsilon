#pragma once

#include "contracts/ILoginView.hpp"
#include "../model/LoginModel.hpp"
#include "../../../core/event/detachment.hpp"

#include <memory>
#include <string>

class LoginPresenter {
public:
    LoginPresenter(std::weak_ptr<ILoginView> view, std::shared_ptr<LoginModel> model);
    void HandleLogin(const std::string& email, const std::string& password);

private:
    std::weak_ptr<ILoginView> m_View;
    std::shared_ptr<LoginModel> m_Model;
    epsilon::core::event::Detachment m_LoginRequestDetachment;
};