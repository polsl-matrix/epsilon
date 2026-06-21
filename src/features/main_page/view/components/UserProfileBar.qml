import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: userProfileRoot

    signal logoutRequested()

    RowLayout {
        anchors.fill: parent
        anchors.margins: 15
        spacing: 12

        Item {
            width: 40
            height: 40

            CircleAvatar {
                anchors.fill: parent
                text: "U"
                fontSize: 16
            }

            Rectangle {
                width: 12
                height: 12
                radius: 6
                color: "#23a559"
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                border.color: "#111111"
                border.width: 2
            }
        }

        ColumnLayout {
            spacing: 2

            Text {
                text: "username123"
                color: "white"
                font.pixelSize: 15
                font.bold: true
            }

            Text {
                text: "online"
                color: "#80848e"
                font.pixelSize: 12
            }
        }

        Item {
            Layout.fillWidth: true
        }

        Image {
            source: "../../../../../resources/users.svg"
            width: 18
            height: 18
            sourceSize.width: 18
            sourceSize.height: 18
            fillMode: Image.PreserveAspectFit

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
            }
        }

        Item {
            width: 18
            height: 18

            Image {
                anchors.fill: parent
                source: "../../../../../resources/settings.svg"
                sourceSize.width: 18
                sourceSize.height: 18
                fillMode: Image.PreserveAspectFit
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: settingsPopup.open()
            }

            Popup {
                id: settingsPopup
                y: 25
                x: -120
                width: 160
                padding: 8

                background: Rectangle {
                    color: "#2b2d31"
                    radius: 8
                    border.color: "#1e1f22"
                    border.width: 1
                }

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 4

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 32
                        radius: 4
                        color: settingsItemHover.containsMouse ? "#313338" : "transparent"

                        RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 8
                            anchors.rightMargin: 8
                            spacing: 8

                            Image {
                                source: "../../../../../resources/settings.svg"
                                width: 16
                                height: 16
                                sourceSize.width: 16
                                sourceSize.height: 16
                            }

                            Text {
                                text: "Settings"
                                color: "#dbdee1"
                                font.pixelSize: 14
                                Layout.fillWidth: true
                            }
                        }

                        MouseArea {
                            id: settingsItemHover
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: settingsPopup.close()
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: "#1e1f22"
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 32
                        radius: 4
                        color: logoutItemHover.containsMouse ? "#313338" : "transparent"

                        RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 8
                            anchors.rightMargin: 8
                            spacing: 8

                            Image {
                                source: "../../../../../resources/exit.svg"
                                width: 16
                                height: 16
                                sourceSize.width: 16
                                sourceSize.height: 16
                            }

                            Text {
                                text: "Log Out"
                                color: "#da373c"
                                font.pixelSize: 14
                                Layout.fillWidth: true
                            }
                        }

                        MouseArea {
                            id: logoutItemHover
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                settingsPopup.close()
                                userProfileRoot.logoutRequested()
                            }
                        }
                    }
                }
            }
        }
    }
}