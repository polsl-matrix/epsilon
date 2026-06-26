import QtQuick
import QtQuick.Layouts

Rectangle {
    id: sideMenuRoot

    signal logoutRequested()
    signal roomSelected(string room_id)

    property var roomsModel: []

    property alias usernameText: userProfileBar.usernameText

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        UserProfileBar {
            id: userProfileBar
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
            model: sideMenuRoot.roomsModel
            onRoomSelected: (room_id) => {
                sideMenuRoot.roomSelected(room_id)
            }
        }

        MenuDivider {}

        CreateServerButton {
            Layout.fillWidth: true
            Layout.preferredHeight: 55
        }
    }
}