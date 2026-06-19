#pragma once

#include "../../../core/event/detachment.hpp"
#include "../model/LoginModel.hpp"
#include "contracts/ILoginPresenter.hpp"
#include "contracts/ILoginView.hpp"

#include <memory>
#include <string>

class LoginPresenter : public ILoginPresenter {
  public:
    LoginPresenter(std::weak_ptr<ILoginView> view,
                   std::shared_ptr<LoginModel> model);
    void HandleLogin(const std::string &email,
                     const std::string &password) override;

  private:
    std::weak_ptr<ILoginView> m_View;
    std::shared_ptr<LoginModel> m_Model;
    epsilon::core::event::Detachment m_LoginRequestDetachment;
};