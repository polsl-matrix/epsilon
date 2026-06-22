#pragma once

#include "../../base/ipresenter.hpp"
#include "contracts/ilogin_view.hpp"
#include "../model/login_model.hpp"
#include "../../../core/event/detachment.hpp"
#include "../../../services/navigation/inavigation_service.hpp"

#include <memory>
#include <string>

namespace epsilon::features::login {

class LoginPresenter : public base::IPresenter {
public:
    LoginPresenter(
        std::unique_ptr<ILoginView> view,
        std::unique_ptr<LoginModel> model,
        std::shared_ptr<services::navigation::INavigationService> navigation_service
    );
    void HandleLogin(const std::string& username, const std::string& password);

private:
    std::shared_ptr<ILoginView> m_View;
    std::shared_ptr<LoginModel> m_Model;
    std::shared_ptr<services::navigation::INavigationService> m_NavigationService;
    epsilon::core::event::Detachment m_LoginRequestDetachment;
};

}
