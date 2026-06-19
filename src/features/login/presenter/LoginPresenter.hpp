#pragma once

#include "../model/LoginModel.hpp"
#include "contracts/ILoginPresenter.hpp"
#include "contracts/ILoginView.hpp"
#include <memory>

class LoginPresenter : public ILoginPresenter {
  public:
    LoginPresenter(std::weak_ptr<ILoginView> view,
                   std::shared_ptr<LoginModel> model);
    void HandleLogin(const std::string &email,
                     const std::string &password) override;

  private:
    std::weak_ptr<ILoginView> m_view;
    std::shared_ptr<LoginModel> m_model;
};