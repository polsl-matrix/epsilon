#pragma once

#include "contracts/ILoginPresenter.hpp"
#include "contracts/ILoginView.hpp"
#include "../model/LoginModel.hpp"

class LoginPresenter : public ILoginPresenter {
public:
    LoginPresenter(ILoginView* view, LoginModel* model);
    void HandleLogin(const std::string& email, const std::string& password) override;

private:
    ILoginView* m_view;
    LoginModel* m_model;
};