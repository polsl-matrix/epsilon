import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
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

            Image {
                source: "../../../../../resources/search.svg"
                width: 14
                height: 14
                sourceSize.width: 14
                sourceSize.height: 14
                fillMode: Image.PreserveAspectFit

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                }
            }
        }
    }
}