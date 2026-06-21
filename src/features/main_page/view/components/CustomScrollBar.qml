import QtQuick
import QtQuick.Controls

ScrollBar {
    id: rootScrollBar

    property color thumbColor: "#4e5058"

    policy: ScrollBar.AsNeeded
    orientation: Qt.Vertical

    background: Item {}

    contentItem: Rectangle {
        implicitWidth: 6
        implicitHeight: 35
        radius: width / 2
        color: rootScrollBar.active ? rootScrollBar.thumbColor : "transparent"

        Behavior on color {
            ColorAnimation {
                duration: 150
            }
        }
    }
}