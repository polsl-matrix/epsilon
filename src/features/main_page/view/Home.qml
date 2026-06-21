import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: homeRoot

    property string activeRoom: ""
    property string activeAvatar: ""

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

            onLogoutRequested: {
                if (typeof homeViewBackend !== "undefined") {
                    homeViewBackend.AttemptLogout()
                }
            }

            onRoomSelected: (selectedRoom, selectedAvatar) => {
                homeRoot.activeRoom = selectedRoom
                homeRoot.activeAvatar = selectedAvatar
            }
        }

        StackLayout {
            SplitView.fillWidth: true
            currentIndex: homeRoot.activeRoom === "" ? 0 : 1

            EmptySpace {}

            ChatRoom {
                roomName: homeRoot.activeRoom
                roomAvatar: homeRoot.activeAvatar
            }
        }
    }
}