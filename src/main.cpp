#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <Qt>

#include <memory>
#include <utility>

#include "features/login/model/login_model.hpp"
#include "features/login/presenter/login_presenter.hpp"
#include "features/login/view/login_view.hpp"

#include "features/main_page/presenter/home_presenter.hpp"
#include "features/main_page/view/home_view.hpp"

#include "router/page_router.hpp"

#include "services/matrix/requests/iraw_request_manager.hpp"
#include "services/matrix/requests/request_manager.hpp"
#include "services/matrix/requests/qt_raw_request_manager.hpp"

#include "services/serialization/json/json_deserialization_strategy.hpp"
#include "services/serialization/json/json_serialization_strategy.hpp"

#include "util/unique_pointer_cast/unique_pointer_cast.hpp"

using epsilon::router::PageRouter;

using epsilon::features::home::HomePresenter;
using epsilon::features::home::HomeView;
using epsilon::features::login::LoginModel;
using epsilon::features::login::LoginPresenter;
using epsilon::features::login::LoginView;

using epsilon::services::matrix::requests::IRawRequestManager;
using epsilon::services::matrix::requests::RequestManager;
using epsilon::services::matrix::requests::qt::QtRawRequestManager;

using epsilon::services::matrix::serialization::Deserializer;
using epsilon::services::matrix::serialization::IDeserializationStrategy;
using epsilon::services::matrix::serialization::ISerializationStrategy;
using epsilon::services::matrix::serialization::Serializer;
using epsilon::services::matrix::serialization::json::JsonDeserializationStrategy;
using epsilon::services::matrix::serialization::json::JsonSerializationStrategy;

using epsilon::util::unique_pointer_cast;

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    const auto backend_url = "";

    auto pageRouter = std::make_shared<PageRouter>();

    auto serializer = std::make_unique<Serializer>(std::make_unique<JsonSerializationStrategy>());
    auto deserializer = std::make_shared<Deserializer>(std::make_unique<JsonDeserializationStrategy>());

    auto request_manager = std::make_unique<RequestManager>(
        backend_url,
        unique_pointer_cast<IRawRequestManager>(std::make_unique<QtRawRequestManager>()),
        std::move(serializer),
        std::move(deserializer)
    );

    auto loginModel = std::make_shared<LoginModel>(
        std::move(request_manager)
    );
    auto loginView = std::make_shared<LoginView>();

    auto loginPresenter =
        std::make_shared<LoginPresenter>(loginView, loginModel);

    auto homeView = std::make_shared<HomeView>();
    auto homePresenter = std::make_shared<HomePresenter>(homeView);

    QObject::connect(loginView.get(), &LoginView::loginSucceeded,
                     pageRouter.get(), [pageRouter]() {
                         pageRouter->NavigateTo(
                             "features/main_page/view/Home.qml");
                     });

    QObject::connect(homeView.get(), &HomeView::logoutSucceeded,
                     pageRouter.get(), [pageRouter]() {
                         pageRouter->NavigateTo(
                             "features/login/view/Login.qml");
                     });

    QObject::connect(homeView.get(), &HomeView::logoutSucceeded,
                     loginView.get(), &LoginView::displayLogoutSuccess);

    engine.rootContext()->setContextProperty("loginViewBackend",
                                             loginView.get());
    engine.rootContext()->setContextProperty("homeViewBackend", homeView.get());
    engine.rootContext()->setContextProperty("pageRouter", pageRouter.get());

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    engine.loadFromModule("Main", "Main");

    return QGuiApplication::exec();
}