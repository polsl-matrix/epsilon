import QtQuick
import QtQuick.Window

Window {
    width: 980
    height: 650
    minimumWidth: 840
    minimumHeight: 580
    visible: true
    title: qsTr("epsilon")

    Home {
        anchors.fill: parent
    }
}