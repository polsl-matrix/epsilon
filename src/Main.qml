import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window {
    id: mainWindow
    width: 980
    height: 650
    minimumWidth: 840
    minimumHeight: 580
    visible: true
    title: qsTr("epsilon")

    StackView {
        id: rootStack
        anchors.fill: parent
        initialItem: "features/login/view/Login.qml"
    }

    Connections {
        target: typeof loginViewBackend !== "undefined" ? loginViewBackend : null

        function onLoginSucceeded() {
            rootStack.replace("features/main_page/view/Home.qml")
        }
    }

    Connections {
        target: typeof homeViewBackend !== "undefined" ? homeViewBackend : null

        function onLogoutSucceeded() {
            rootStack.replace("features/login/view/Login.qml")
        }
    }
}