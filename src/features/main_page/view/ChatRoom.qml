import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: chatRoomRoot

    property string roomName: ""
    property string roomAvatar: ""

    color: "#1e1f22"

    component MessageItem : ColumnLayout {
        property string messageText: ""
        property bool isSenderMe: false

        width: ListView.view.width

        Rectangle {
            Layout.alignment: isSenderMe ? Qt.AlignRight : Qt.AlignLeft
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            radius: 14
            color: isSenderMe ? "#0078d7" : "#2b2d31"
            Layout.maximumWidth: 450
            implicitWidth: contentText.implicitWidth + 24
            implicitHeight: contentText.implicitHeight + 18

            Text {
                id: contentText
                text: messageText
                color: "white"
                font.pixelSize: 14
                wrapMode: Text.Wrap
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
                anchors.margins: 10
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        ListView {
            id: chatListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 16
            topMargin: 125
            bottomMargin: 20

            ScrollBar.vertical: CustomScrollBar {
                thumbColor: "#4e5058"
            }

            model: ListModel {
                ListElement {
                    text: "Hey! Are we still working on the epsilon architecture?"
                    isMe: false
                }
                ListElement {
                    text: "Yes, backend is fully detached now. Working on the chat UI."
                    isMe: true
                }
                ListElement {
                    text: "Awesome. The custom event system is extremely fast."
                    isMe: false
                }
                ListElement {
                    text: "Did you check the new CMake configuration?"
                    isMe: true
                }
                ListElement {
                    text: "Everything compiles without any warnings or errors."
                    isMe: false
                }
                ListElement {
                    text: "Great! Now let's test how the scrolling behaves with many messages."
                    isMe: true
                }
                ListElement {
                    text: "Adding a few more lines to fill up the screen completely."
                    isMe: false
                }
                ListElement {
                    text: "This should push the top messages under the fading overlay."
                    isMe: true
                }
                ListElement {
                    text: "Looks really clean, exactly like iMessage."
                    isMe: false
                }
                ListElement {
                    text: "We also need animations for the send button and the header."
                    isMe: true
                }
                ListElement {
                    text: "And replacing the text arrow with an SVG icon."
                    isMe: false
                }
                ListElement {
                    text: "Now testing the refined top gradient overlay."
                    isMe: true
                }
                ListElement {
                    text: "It uses pure alpha channel interpolation to avoid gray smudges."
                    isMe: false
                }
                ListElement {
                    text: "And the scrollbar appears dynamically only while moving."
                    isMe: true
                }
            }

            delegate: MessageItem {
                messageText: model.text
                isSenderMe: model.isMe
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 75

            Rectangle {
                anchors.fill: parent
                anchors.margins: 12
                radius: height / 2
                color: "#2b2d31"

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 16
                    anchors.rightMargin: 6
                    spacing: 10

                    TextField {
                        Layout.fillWidth: true
                        placeholderText: "Message " + chatRoomRoot.roomName
                        placeholderTextColor: "#80848e"
                        color: "white"
                        font.pixelSize: 14
                        background: Item {}
                        verticalAlignment: TextInput.AlignVCenter
                    }

                    Rectangle {
                        width: 36
                        height: 36
                        radius: 18
                        color: "#0078d7"
                        scale: sendMouseArea.pressed ? 0.85 : 1.0

                        Behavior on scale {
                            NumberAnimation {
                                duration: 100
                            }
                        }

                        Image {
                            source: "../../../../resources/send.svg"
                            anchors.centerIn: parent
                            width: 16
                            height: 16
                            sourceSize.width: 16
                            sourceSize.height: 16
                        }

                        MouseArea {
                            id: sendMouseArea
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                        }
                    }
                }
            }
        }
    }

    Item {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 115

        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: Qt.rgba(30/255, 31/255, 34/255, 1.0)
                }
                GradientStop {
                    position: 0.5
                    color: Qt.rgba(30/255, 31/255, 34/255, 0.9)
                }
                GradientStop {
                    position: 0.8
                    color: Qt.rgba(30/255, 31/255, 34/255, 0.4)
                }
                GradientStop {
                    position: 1.0
                    color: Qt.rgba(30/255, 31/255, 34/255, 0.0)
                }
            }
        }

        ColumnLayout {
            id: headerColumn
            anchors.centerIn: parent
            spacing: 6
            scale: headerMouseArea.pressed ? 0.92 : 1.0

            Behavior on scale {
                NumberAnimation {
                    duration: 100
                }
            }

            Rectangle {
                width: 44
                height: 44
                radius: 22
                color: "#584168"
                Layout.alignment: Qt.AlignHCenter
                clip: true

                Text {
                    anchors.centerIn: parent
                    text: chatRoomRoot.roomAvatar.length === 1 ? chatRoomRoot.roomAvatar : ""
                    color: "white"
                    font.pixelSize: 18
                    font.bold: true
                }

                Image {
                    anchors.fill: parent
                    source: chatRoomRoot.roomAvatar.length > 1 ? chatRoomRoot.roomAvatar : ""
                    fillMode: Image.PreserveAspectCrop
                    visible: chatRoomRoot.roomAvatar.length > 1
                }
            }

            Rectangle {
                Layout.alignment: Qt.AlignHCenter
                implicitWidth: nameRow.implicitWidth + 24
                implicitHeight: 26
                radius: 13
                color: "#111214"
                border.color: "#2b2d31"
                border.width: 1

                RowLayout {
                    id: nameRow
                    anchors.centerIn: parent
                    spacing: 6

                    Text {
                        text: chatRoomRoot.roomName
                        color: "white"
                        font.pixelSize: 13
                        font.bold: true
                    }

                    Image {
                        source: "../../../../resources/arrow.svg"
                        width: 10
                        height: 10
                        sourceSize.width: 10
                        sourceSize.height: 10
                    }
                }
            }
        }

        MouseArea {
            id: headerMouseArea
            anchors.fill: headerColumn
            cursorShape: Qt.PointingHandCursor
        }
    }
}