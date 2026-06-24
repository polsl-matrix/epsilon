import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: detailsPopupRoot

    property string roomName: ""
    property string roomAvatar: ""
    property string roomId: "!matrix_room_id_9921:epsilon.local"

    modal: true
    focus: true
    x: Math.round((parent.width - width) / 2)
    y: Math.round((parent.height - height) / 2)
    width: 320
    height: 450

    background: Rectangle {
        color: "#2b2d31"
        radius: 12
        border.color: "#1e1f22"
        border.width: 1
    }

    contentItem: ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 16

        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 8

            CircleAvatar {
                width: 72
                height: 72
                text: detailsPopupRoot.roomAvatar.length === 1 ? detailsPopupRoot.roomAvatar : ""
                imageSource: detailsPopupRoot.roomAvatar.length > 1 ? detailsPopupRoot.roomAvatar : ""
                fontSize: 28
                Layout.alignment: Qt.AlignHCenter
            }

            Text {
                text: detailsPopupRoot.roomName
                color: "white"
                font.pixelSize: 18
                font.bold: true
                Layout.alignment: Qt.AlignHCenter
            }

            Text {
                text: detailsPopupRoot.roomId
                color: "#80848e"
                font.pixelSize: 11
                Layout.alignment: Qt.AlignHCenter
                textFormat: Text.PlainText
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: "#1e1f22"
        }

        Text {
            text: "MEMBERS - " + membersListView.count
            color: "#949ba4"
            font.pixelSize: 12
            font.bold: true
        }

        ListView {
            id: membersListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 12

            ScrollBar.vertical: CustomScrollBar {
                thumbColor: "#1e1f22"
            }

            model: ListModel {
                ListElement {
                    name: "Pietrek14"
                    avatar: "P"
                }
                ListElement {
                    name: "username123"
                    avatar: "U"
                }
                ListElement {
                    name: "Staszek"
                    avatar: "S"
                }
                ListElement {
                    name: "Ewa"
                    avatar: "E"
                }
                ListElement {
                    name: "Janek"
                    avatar: "J"
                }
            }

            delegate: RowLayout {
                width: ListView.view.width
                spacing: 12

                CircleAvatar {
                    width: 32
                    height: 32
                    text: model.avatar
                    fontSize: 14
                }

                Text {
                    text: model.name
                    color: "white"
                    font.pixelSize: 14
                    font.bold: model.name === "username123"
                    Layout.fillWidth: true
                }
            }
        }
    }
}