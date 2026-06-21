import QtQuick
import QtQuick.Layouts

Item {
    signal clicked()

    Rectangle {
        anchors.fill: parent
        color: addServerMouseArea.containsMouse ? "#2b2d31" : "transparent"
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 20
        spacing: 15

        Image {
            source: "../../../../../resources/plus.svg"
            width: 24
            height: 24
            sourceSize.width: 24
            sourceSize.height: 24
            fillMode: Image.PreserveAspectFit
        }

        Text {
            text: "Create a new server"
            color: "white"
            font.pixelSize: 14
        }

        Item {
            Layout.fillWidth: true
        }
    }

    MouseArea {
        id: addServerMouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: parent.clicked()
    }
}