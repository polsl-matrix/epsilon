import QtQuick
import QtQuick.Layouts

Rectangle {
    id: sideMenuRoot

    signal logoutRequested()
    signal roomSelected(string roomName, string roomAvatar)

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        UserProfileBar {
            Layout.fillWidth: true
            Layout.preferredHeight: 75
            onLogoutRequested: {
                sideMenuRoot.logoutRequested()
            }
        }

        SpaceSearchBar {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
        }

        MenuDivider {}

        RoomListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            onRoomSelected: (name, avatar) => {
                sideMenuRoot.roomSelected(name, avatar)
            }
        }

        MenuDivider {}

        CreateServerButton {
            Layout.fillWidth: true
            Layout.preferredHeight: 55
        }
    }
}