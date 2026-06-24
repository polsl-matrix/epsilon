#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <Qt>

#include <memory>
#include <string>
#include <utility>

#include "services/matrix/requests/iraw_request_manager.hpp"
#include "services/matrix/requests/qt_raw_request_manager.hpp"
#include "services/matrix/requests/request_manager.hpp"

#include "services/navigation/args/login_screen_args.hpp"
#include "services/navigation/navigation_service.hpp"
#include "services/navigation/screen.hpp"

#include "services/router/page_router.hpp"

#include "services/matrix/requests/iraw_request_manager.hpp"
#include "services/matrix/requests/qt_raw_request_manager.hpp"
#include "services/matrix/requests/request_manager.hpp"

#include "services/serialization/json/json_deserialization_strategy.hpp"
#include "services/serialization/json/json_serialization_strategy.hpp"

#include "util/unique_pointer_cast/unique_pointer_cast.hpp"

using epsilon::services::matrix::requests::IRawRequestManager;
using epsilon::services::matrix::requests::RequestManager;
using epsilon::services::matrix::requests::qt::QtRawRequestManager;

using epsilon::services::matrix::serialization::Deserializer;
using epsilon::services::matrix::serialization::IDeserializationStrategy;
using epsilon::services::matrix::serialization::ISerializationStrategy;
using epsilon::services::matrix::serialization::Serializer;
using epsilon::services::matrix::serialization::json::JsonDeserializationStrategy;
using epsilon::services::matrix::serialization::json::JsonSerializationStrategy;

using epsilon::services::navigation::NavigationService;
using epsilon::services::navigation::Screen;
using epsilon::services::navigation::args::LoginScreenArgs;

using epsilon::services::router::PageRouter;

using epsilon::util::unique_pointer_cast;

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    const auto backend_url = "http://127.0.0.1:8080";

    auto page_router = std::make_shared<PageRouter>(engine.rootContext());

    auto serializer = std::make_unique<Serializer>(
        std::make_unique<JsonSerializationStrategy>());
    auto deserializer = std::make_shared<Deserializer>(
        std::make_unique<JsonDeserializationStrategy>());

    auto request_manager = std::make_shared<RequestManager>(
        backend_url,
        unique_pointer_cast<IRawRequestManager>(
            std::make_unique<QtRawRequestManager>()),
        std::move(serializer), std::move(deserializer));

    auto navigation_service = std::make_shared<NavigationService>(page_router);

    auto login_screen_args =
        LoginScreenArgs{ request_manager, navigation_service };

    navigation_service->NavigateTo(Screen::Login, login_screen_args);

    // QObject::connect(homeView.get(), &HomeView::logoutSucceeded,
    //                  pageRouter.get(), [pageRouter]() {
    //                      pageRouter->NavigateTo(
    //                          "features/login/view/Login.qml");
    //                  });

    // QObject::connect(homeView.get(), &HomeView::logoutSucceeded,
    //                  loginView.get(), &LoginView::DisplayLogoutSuccess);

    engine.rootContext()->setContextProperty("pageRouter", page_router.get());

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    engine.loadFromModule("Main", "Main");

    return QGuiApplication::exec();
}