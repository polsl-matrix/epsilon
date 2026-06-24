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

    model: ListModel {
        ListElement {
            room_id: "!catlovers:epsilon"
            name: "Cat Lovers"
            avatar: "C"
            notif: 0
        }
        ListElement {
            room_id: "!myserver:epsilon"
            name: "My Server #1"
            avatar: "M"
            notif: 67
        }
        ListElement {
            room_id: "!doggies:epsilon"
            name: "Dog Aficionados"
            avatar: "D"
            notif: 1
        }
        ListElement {
            room_id: "!neighbour:epsilon"
            name: "FriendlyNeighbour23"
            avatar: "F"
            notif: 0
        }
        ListElement {
            room_id: "!furry:epsilon"
            name: "Furry Corn"
            avatar: "F"
            notif: 0
        }
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
                text: model.avatar.length === 1 ? model.avatar : ""
                imageSource: model.avatar.length > 1 ? model.avatar : ""
                fontSize: 14
            }

            Text {
                text: model.name
                color: "white"
                font.pixelSize: 14
            }

            Item {
                Layout.fillWidth: true
            }

            Rectangle {
                visible: model.notif > 0
                width: Math.max(24, notifText.width + 12)
                height: 18
                radius: 9
                color: "#da373c"

                Text {
                    id: notifText
                    anchors.centerIn: parent
                    text: model.notif > 0 ? model.notif : ""
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
                roomListRoot.roomSelected(model.room_id)
            }
        }
    }
}