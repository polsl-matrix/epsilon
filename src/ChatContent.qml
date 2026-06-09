import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: chatContentRoot

    Item {
        id: headerArea
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 15
        height: 40

        Rectangle {
            width: titleText.implicitWidth + 40
            height: 40
            radius: 20
            color: "#444444"
            anchors.centerIn: parent

            Text {
                id: titleText
                text: "Server/Person Name"
                color: "white"
                font.pixelSize: 14
                font.bold: true
                anchors.centerIn: parent
            }
        }

        Rectangle {
            width: 40
            height: 40
            radius: 20
            color: "#444444"
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

            Text {
                text: "i"
                color: "white"
                font.pixelSize: 18
                font.bold: true
                font.italic: true
                anchors.centerIn: parent
            }
        }
    }

    RowLayout {
        id: footerArea
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 15
        spacing: 15

        Rectangle {
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            radius: 20
            color: "#444444"

            Text {
                text: "📎"
                color: "white"
                font.pixelSize: 18
                anchors.centerIn: parent
            }
        }

        TextField {
            id: messageInput
            placeholderText: "Type a message..."
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            color: "white"
            verticalAlignment: TextInput.AlignVCenter
            padding: 0
            leftPadding: 15
            rightPadding: 15

            background: Rectangle {
                color: "#444444"
                radius: 20
                border.color: messageInput.activeFocus ? "#0078d7" : "transparent"
                border.width: 1
            }
        }

        Rectangle {
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            radius: 20
            color: "#444444"

            Text {
                text: "➤"
                color: "white"
                font.pixelSize: 16
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: 1
            }
        }
    }
}