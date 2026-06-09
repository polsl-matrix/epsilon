import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: sidebarRoot

    property bool isMenuOpen: true
    property int currentMenuWidth: 220

    signal toggleMenu()
    signal resizeRequested(real mappedX)

    width: isMenuOpen ? currentMenuWidth : 70
    height: parent.height - 30
    radius: 35
    clip: true

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#2a2a2a" }
        GradientStop { position: 1.0; color: "#373737" }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 15
        spacing: 15

        RowLayout {
            Layout.fillWidth: true
            spacing: 15

            Rectangle {
                Layout.preferredWidth: 40
                Layout.preferredHeight: 40
                radius: 20
                color: sidebarRoot.isMenuOpen ? (toggleArea.containsMouse ? "#444444" : "transparent") : (toggleArea.pressed ? "#112937" : (toggleArea.containsMouse ? "#1F4C66" : "transparent"))

                Text {
                    text: "☰"
                    color: "white"
                    font.pixelSize: 18
                    font.bold: sidebarRoot.isMenuOpen
                    anchors.centerIn: parent
                }

                MouseArea {
                    id: toggleArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: sidebarRoot.toggleMenu()
                }
            }

            TextField {
                id: searchInput
                placeholderText: "Search..."
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                visible: sidebarRoot.isMenuOpen
                color: "white"
                verticalAlignment: TextInput.AlignVCenter
                padding: 0
                leftPadding: 15
                rightPadding: 15

                background: Rectangle {
                    color: "#1d1d1d"
                    radius: 20
                    border.color: searchInput.activeFocus ? "#0078d7" : "transparent"
                    border.width: 1
                }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignTop
            spacing: 10

            Repeater {
                model: [
                    { name: "Alice Smith", bg: "#e67e22" },
                    { name: "Bob Ross", bg: "#2ecc71" }
                ]

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 40
                    radius: 20
                    color: sidebarRoot.isMenuOpen ? "#444444" : "transparent"

                    Rectangle {
                        width: 30
                        height: 30
                        radius: 15
                        color: modelData.bg
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                    }

                    Text {
                        text: modelData.name
                        visible: sidebarRoot.isMenuOpen
                        color: "white"
                        font.pixelSize: 14
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 45
                    }
                }
            }

            Item {
                Layout.fillHeight: true
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 15

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                radius: 20
                color: sidebarRoot.isMenuOpen ? "#444444" : "transparent"

                Rectangle {
                    width: 30
                    height: 30
                    radius: 15
                    color: "#0078d7"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }

                Text {
                    text: "John Doe"
                    visible: sidebarRoot.isMenuOpen
                    color: "white"
                    font.pixelSize: 14
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 45
                }
            }

            Rectangle {
                visible: sidebarRoot.isMenuOpen
                Layout.preferredWidth: 40
                Layout.preferredHeight: 40
                radius: 20
                color: "#0078d7"

                Text {
                    text: "+"
                    color: "white"
                    font.pixelSize: 26
                    anchors.centerIn: parent
                }
            }
        }
    }

    MouseArea {
        id: resizeHandle
        width: 10
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        cursorShape: Qt.SizeHorCursor
        visible: sidebarRoot.isMenuOpen
        z: 10

        onPositionChanged: (mouse) => {
            if (pressed) {
                let mappedX = mapToItem(sidebarRoot, mouse.x, mouse.y).x
                sidebarRoot.resizeRequested(mappedX)
            }
        }
    }
}