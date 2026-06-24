import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: homeRoot

    property string activeRoom: ""

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

            roomsModel: typeof homeViewBackend !== "undefined" ? homeViewBackend.rooms : []

            onLogoutRequested: {
                if (typeof homeViewBackend !== "undefined") {
                    homeViewBackend.AttemptLogout()
                }
            }

            onRoomSelected: (room_id) => {
                homeRoot.activeRoom = room_id
                if (typeof homeViewBackend !== "undefined") {
                    homeViewBackend.SelectRoom(room_id)
                }
            }
        }

        StackLayout {
            SplitView.fillWidth: true
            currentIndex: homeRoot.activeRoom === "" ? 0 : 1

            EmptySpace {}

            Loader {
                id: chatLoader
            }
        }
    }

    Connections {
        target: typeof homeViewBackend !== "undefined" ? homeViewBackend : null
        function onChatRoomLoaded() {
            chatLoader.source = ""
            chatLoader.source = "../../chat_room/view/ChatRoom.qml"
        }
    }
}