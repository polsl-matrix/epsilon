#pragma once

#include "../../base/ipresenter.hpp"
#include "contracts/ihome_view.hpp"
#include "../model/home_model.hpp"
#include "../../chat_room/presenter/chat_room_presenter.hpp"
#include "../../../core/event/util/action.hpp"
#include "../../../services/navigation/inavigation_service.hpp"

#include <memory>

namespace epsilon::features::home {

class HomePresenter : public base::IPresenter {
    using INavigationService = services::navigation::INavigationService;

    std::shared_ptr<INavigationService> m_NavigationService;

    template<typename... T>
    using Action = core::event::util::Action<T...>;

    std::shared_ptr<Action<std::string>> m_SelectRoomEventHandle;
    std::shared_ptr<Action<>> m_LogoutEventHandle;

  public:
    explicit HomePresenter(std::unique_ptr<IHomeView> view, std::unique_ptr<HomeModel> model, std::shared_ptr<INavigationService> navigation_service);
    void HandleLogout();

  private:
    void UpdateUserName();

    std::shared_ptr<IHomeView> m_View;
    std::unique_ptr<HomeModel> m_Model;

    std::unique_ptr<chat_room::ChatRoomPresenter> m_OpenRoom;
};

}
