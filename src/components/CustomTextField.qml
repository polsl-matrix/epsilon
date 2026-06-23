import QtQuick
import QtQuick.Controls

TextField {
    id: customInputRoot

    color: "white"
    font.pixelSize: 14
    verticalAlignment: TextInput.AlignVCenter
    selectionColor: "#5865f2"
    placeholderTextColor: "#80848e"
    leftPadding: 12
    rightPadding: 12

    background: Rectangle {
        radius: 8
        color: "#1e1f22"
        border.color: customInputRoot.activeFocus ? "#0078d7" : "#313338"
        border.width: customInputRoot.activeFocus ? 2 : 1
    }
}