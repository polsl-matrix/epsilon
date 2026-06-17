import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    component Divider : Rectangle {
        Layout.fillWidth: true
        height: 1
        color: "#1e1f22"
    }

    component ListDivider : Rectangle {
        height: 1
        color: "#1e1f22"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 15
        anchors.rightMargin: 15
    }

    component BaseText : Text {
        color: "white"
        font.pixelSize: 14
    }

    component IconText : Text {
        color: "#b5bac1"
        font.pixelSize: 18
    }

    component SvgIcon : Image {
        width: 18
        height: 18
        sourceSize.width: 18
        sourceSize.height: 18
        fillMode: Image.PreserveAspectFit
    }

    component CircleAvatar : Rectangle {
        property alias text: avatarText.text
        property alias fontSize: avatarText.font.pixelSize
        radius: height / 2
        color: "#333333"

        Text {
            id: avatarText
            anchors.centerIn: parent
            color: "white"
            font.bold: true
        }
    }

    component HandMouseArea : MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 75

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
                    BaseText {
                        text: "username123"
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

                SvgIcon {
                    source: "../../../../resources/users.svg"
                    HandMouseArea {}
                }

                SvgIcon {
                    source: "../../../../resources/settings.svg"
                    HandMouseArea {}
                }
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 50

            Rectangle {
                anchors.fill: parent
                anchors.leftMargin: 15
                anchors.rightMargin: 15
                anchors.bottomMargin: 15
                color: "white"
                radius: 18

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 12
                    anchors.rightMargin: 12

                    TextField {
                        Layout.fillWidth: true
                        placeholderText: "Search for a space"
                        placeholderTextColor: "#80848e"
                        color: "#313338"
                        font.pixelSize: 13
                        verticalAlignment: TextInput.AlignVCenter
                        selectionColor: "#5865f2"
                        background: Item {}
                        padding: 0
                        clip: true
                    }

                    SvgIcon {
                        source: "../../../../resources/search.svg"
                        width: 14
                        height: 14
                        HandMouseArea {}
                    }
                }
            }
        }

        Divider {}

        ListView {
            id: serversList
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AsNeeded
            }

            model: ListModel {
                ListElement { name: "Cat Lovers"; notif: 0 }
                ListElement { name: "My Server #1"; notif: 67 }
                ListElement { name: "Dog Aficionados"; notif: 1 }
                ListElement { name: "FriendlyNeighbour23"; notif: 0 }
                ListElement { name: "Furry Corn"; notif: 0 }
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
                        text: model.name.charAt(0)
                        fontSize: 14
                    }

                    BaseText {
                        text: model.name
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

                        BaseText {
                            id: notifText
                            anchors.centerIn: parent
                            text: model.notif > 0 ? model.notif : ""
                            font.pixelSize: 11
                            font.bold: true
                        }
                    }
                }
                ListDivider {}
                HandMouseArea {
                    id: itemMouseArea
                }
            }
        }

        Divider {}

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 55

            Rectangle {
                anchors.fill: parent
                color: addServerMouseArea.containsMouse ? "#2b2d31" : "transparent"
            }

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 20
                spacing: 15

                SvgIcon {
                    source: "../../../../resources/plus.svg"
                    width: 24
                    height: 24
                }

                BaseText {
                    text: "Create a new server"
                }

                Item {
                    Layout.fillWidth: true
                }
            }
            HandMouseArea {
                id: addServerMouseArea
            }
        }
    }
}