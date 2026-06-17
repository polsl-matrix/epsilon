import QtQuick
import QtQuick.Controls

Rectangle {
    color: "#1d1d1d"

    SplitView {
        anchors.fill: parent

        handle: Rectangle {
            implicitWidth: 4
            color: "transparent"

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.SizeHorCursor
                acceptedButtons: Qt.NoButton
            }
        }

        SideMenu {
            SplitView.preferredWidth: 280
            SplitView.minimumWidth: 270
            SplitView.maximumWidth: 350
            color: "#111111"
        }

        EmptySpace {
            SplitView.fillWidth: true
        }
    }
}