#pragma once

#include "../../base/ipresenter.hpp"
#include "contracts/iregistration_view.hpp"
#include "../model/registration_model.hpp"
#include "../../../core/event/util/action.hpp"
#include "../../../services/navigation/inavigation_service.hpp"

#include <memory>
#include <string>

namespace epsilon::features::registration {

class RegistrationPresenter : public base::IPresenter {
public:
    RegistrationPresenter(
        std::unique_ptr<IRegistrationView> view,
        std::unique_ptr<RegistrationModel> model,
        std::shared_ptr<services::navigation::INavigationService> navigation_service
    );

private:
    void HandleRegistration(const std::string &username, const std::string &password, const std::string &repeat_password);

    std::shared_ptr<IRegistrationView> m_View;
    std::shared_ptr<RegistrationModel> m_Model;
    std::shared_ptr<services::navigation::INavigationService> m_NavigationService;

    template<typename... T>
    using Action = epsilon::core::event::util::Action<T...>;

    std::shared_ptr<Action<std::string, std::string, std::string>> m_RegistrationRequestEventHandle;
    std::shared_ptr<Action<>> m_LoginLinkEventHandle;
};

}