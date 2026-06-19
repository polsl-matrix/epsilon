#include <QCoreApplication>
#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <Qt>
#include <memory>

#include "src/features/login/model/LoginModel.hpp"
#include "src/features/login/presenter/LoginPresenter.hpp"
#include "src/features/login/view/LoginView.hpp"

#include "src/features/main_page/presenter/HomePresenter.hpp"
#include "src/features/main_page/view/HomeView.hpp"

#include "src/router/PageRouter.hpp"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    auto pageRouter = std::make_shared<PageRouter>();

    auto loginModel = std::make_shared<LoginModel>();
    auto loginView = std::make_shared<LoginView>();
    auto loginPresenter =
        std::make_shared<LoginPresenter>(loginView, loginModel);
    loginView->setPresenter(loginPresenter);

    auto homeView = std::make_shared<HomeView>();
    auto homePresenter = std::make_shared<HomePresenter>(homeView);

    QObject::connect(loginView.get(), &LoginView::loginSucceeded,
                     pageRouter.get(), [pageRouter]() {
                         pageRouter->navigateTo(
                             "features/main_page/view/Home.qml");
                     });

    QObject::connect(homeView.get(), &HomeView::logoutSucceeded,
                     pageRouter.get(), [pageRouter]() {
                         pageRouter->navigateTo(
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