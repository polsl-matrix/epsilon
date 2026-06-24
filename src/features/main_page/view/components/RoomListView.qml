import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ListView {
    id: roomListRoot

    signal roomSelected(string room_id)

    clip: true
    boundsBehavior: Flickable.StopAtBounds

    ScrollBar.vertical: CustomScrollBar {
        thumbColor: "#313338"
    }

    delegate: Rectangle {
        width: ListView.view.width
        height: 50
        color: itemMouseArea.containsMouse ? "#2b2d31" : "transparent"

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 15
            anchors.rightMargin: 15
            spacing: 12

            CircleAvatar {
                width: 32
                height: 32
                text: modelData.avatar.length === 1 ? modelData.avatar : ""
                imageSource: modelData.avatar.length > 1 ? modelData.avatar : ""
                fontSize: 14
            }

            Text {
                text: modelData.name
                color: "white"
                font.pixelSize: 14
            }

            Item {
                Layout.fillWidth: true
            }

            Rectangle {
                visible: modelData.notif > 0
                width: Math.max(24, notifText.width + 12)
                height: 18
                radius: 9
                color: "#da373c"

                Text {
                    id: notifText
                    anchors.centerIn: parent
                    text: modelData.notif > 0 ? modelData.notif : ""
                    color: "white"
                    font.pixelSize: 11
                    font.bold: true
                }
            }
        }

        Rectangle {
            height: 1
            color: "#1e1f22"
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 15
            anchors.rightMargin: 15
        }

        MouseArea {
            id: itemMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                roomListRoot.roomSelected(modelData.room_id)
            }
        }
    }
}