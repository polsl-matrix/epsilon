import QtQuick

Rectangle {
    property alias text: avatarText.text
    property alias fontSize: avatarText.font.pixelSize
    property string imageSource: ""

    radius: height / 2
    color: "#333333"
    clip: true

    Text {
        id: avatarText
        anchors.centerIn: parent
        color: "white"
        font.bold: true
        visible: parent.imageSource.length === 0
    }

    Image {
        anchors.fill: parent
        source: parent.imageSource
        fillMode: Image.PreserveAspectCrop
        visible: parent.imageSource.length > 0
    }
}