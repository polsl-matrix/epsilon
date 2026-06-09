import QtQuick
import QtQuick.Window

Window {
    width: 640
    height: 480
    minimumWidth: 600
    minimumHeight: 330
    visible: true
    title: qsTr("epsilon")

    Rectangle {
        anchors.fill: parent
        color: "#1d1d1d"
    }

    Login {
        anchors.fill: parent
    }
}