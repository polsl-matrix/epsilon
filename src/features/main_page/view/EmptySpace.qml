import QtQuick

Rectangle {
    color: "#1E1E1E"

    component EmptySpaceText : Text {
        color: "#8F8F8F"
        font.family: "Times New Roman"
        anchors.horizontalCenter: parent.horizontalCenter
        height: paintedHeight
        verticalAlignment: Text.AlignVCenter
    }

    Column {
        anchors.centerIn: parent
        spacing: 15

        EmptySpaceText {
            text: "ε"
            font.pixelSize: 256
        }

        EmptySpaceText {
            text: "Nothing to see here"
            font.pixelSize: 32
        }

        EmptySpaceText {
            text: "Open a room to start chatting"
            font.pixelSize: 16
        }
    }
}