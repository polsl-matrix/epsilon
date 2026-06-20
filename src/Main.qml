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
        target: typeof pageRouter !== "undefined" ? pageRouter : null

        function onNavigateRequested(path) {
            rootStack.replace(path)
        }
    }
}