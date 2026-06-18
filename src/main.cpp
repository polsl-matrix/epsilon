#include <QCoreApplication>
#include <QGuiApplication>
#include <QObject>
#include <Qt>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/features/login/model/LoginModel.hpp"
#include "src/features/login/view/LoginView.hpp"
#include "src/features/login/presenter/LoginPresenter.hpp"

#include "src/features/main_page/view/HomeView.hpp"
#include "src/features/main_page/presenter/HomePresenter.hpp"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    LoginModel loginModel;
    LoginView loginView;
    LoginPresenter loginPresenter(&loginView, &loginModel);
    loginView.setPresenter(&loginPresenter);

    HomeView homeView;
    HomePresenter homePresenter(&homeView);
    homeView.setPresenter(&homePresenter);

    QObject::connect(&homeView, &HomeView::logoutSucceeded, &loginView, &LoginView::displayLogoutSuccess);

    engine.rootContext()->setContextProperty("loginViewBackend", &loginView);
    engine.rootContext()->setContextProperty("homeViewBackend", &homeView);

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    engine.loadFromModule("Main", "Main");

    return QGuiApplication::exec();
}