import QtQuick
import QtQuick.Layouts

Item {
    id: exposeRoot

    property bool isMenuOpen: true
    property real menuWidthRatio: 0.35
    property int currentMenuWidth: Math.max(220, Math.min(width * menuWidthRatio, width / 2))
    property int minCalculatedWidth: isMenuOpen && menuWidthRatio > 0 ? Math.max(800, 220 / menuWidthRatio) : 800
    property int minCalculatedHeight: 500

    implicitWidth: minCalculatedWidth
    implicitHeight: minCalculatedHeight

    SidebarMenu {
        id: sidebarMenu
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 15

        isMenuOpen: exposeRoot.isMenuOpen
        currentMenuWidth: exposeRoot.currentMenuWidth

        onToggleMenu: exposeRoot.isMenuOpen = !exposeRoot.isMenuOpen

        onResizeRequested: (mappedX) => {
            let clampedWidth = Math.min(Math.max(220, mappedX), exposeRoot.width / 2)
            exposeRoot.menuWidthRatio = clampedWidth / exposeRoot.width
        }
    }

    // DefaultContent {
    //     anchors.left: sidebarMenu.right
    //     anchors.right: parent.right
    //     anchors.top: parent.top
    //     anchors.bottom: parent.bottom
    // }

    ChatContent {
        anchors.left: sidebarMenu.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }
}