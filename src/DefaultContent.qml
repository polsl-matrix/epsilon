import QtQuick
import QtQuick.Layouts

Item {
    id: contentRoot

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 10

        Text {
            text: "ℰ"
            color: "#777777"
            font.pixelSize: 120
            font.family: "Times New Roman"
            Layout.alignment: Qt.AlignHCenter
        }

        Text {
            text: "Nothing to see here"
            color: "#999999"
            font.pixelSize: 24
            font.family: "Times New Roman"
            Layout.alignment: Qt.AlignHCenter
        }

        Text {
            text: "Open a room to start chatting"
            color: "#666666"
            font.pixelSize: 14
            Layout.alignment: Qt.AlignHCenter
        }
    }
}