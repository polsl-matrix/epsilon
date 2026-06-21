#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <Qt>
#include <QCoreApplication>


#include <memory>

#include "src/features/login/model/login_model.hpp"
#include "src/features/login/presenter/login_presenter.hpp"
#include "src/features/login/view/login_view.hpp"

#include "src/features/main_page/presenter/home_presenter.hpp"
#include "src/features/main_page/view/home_view.hpp"

#include "src/router/page_router.hpp"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    auto pageRouter = std::make_shared<PageRouter>(engine.rootContext());

    auto loginModel = std::make_shared<LoginModel>();
    auto loginView = std::make_shared<LoginView>();
    auto loginPresenter = std::make_shared<LoginPresenter>(loginView, loginModel);

    auto homeView = std::make_shared<HomeView>();
    auto homePresenter = std::make_shared<HomePresenter>(homeView);

    QObject::connect(loginView.get(), &LoginView::loginSucceeded, pageRouter.get(), [pageRouter]() {
        pageRouter->NavigateTo("features/main_page/view/Home.qml");
    });

    QObject::connect(homeView.get(), &HomeView::logoutSucceeded, pageRouter.get(), [pageRouter]() {
        pageRouter->NavigateTo("features/login/view/Login.qml");
    });

    QObject::connect(homeView.get(), &HomeView::logoutSucceeded, loginView.get(), &LoginView::displayLogoutSuccess);

    engine.rootContext()->setContextProperty("loginViewBackend", loginView.get());
    engine.rootContext()->setContextProperty("homeViewBackend", homeView.get());
    engine.rootContext()->setContextProperty("pageRouter", pageRouter.get());

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    engine.loadFromModule("Main", "Main");

    return QGuiApplication::exec();
}