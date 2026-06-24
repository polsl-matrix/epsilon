import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects
import "../../../components"

Rectangle {
    id: registrationRoot

    color: "#1d1d1d"

    component FormLabel : Text {
        color: "white"
        font.pixelSize: 14
    }

    Item {
        id: formContainer
        anchors.centerIn: parent
        width: Math.min(450, parent.width - 60)
        height: Math.min(520, parent.height - 40)

        Rectangle {
            id: backgroundCard
            anchors.fill: parent
            radius: 15
            visible: false
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: "#2a2a2a"
                }
                GradientStop {
                    position: 1.0
                    color: "#373737"
                }
            }
        }

        MultiEffect {
            source: backgroundCard
            anchors.fill: backgroundCard
            shadowEnabled: true
            shadowColor: "#5f5f5f"
            shadowBlur: 0.4
            shadowVerticalOffset: 0
            shadowHorizontalOffset: 0
        }

        ColumnLayout {
            id: formLayout
            anchors.centerIn: parent
            spacing: 20

            Text {
                text: "Create an Account"
                color: "white"
                Layout.alignment: Qt.AlignHCenter
                font.pixelSize: 24
                padding: 10
            }

            Text {
                id: errorTextLabel
                color: "#da373c"
                font.pixelSize: 12
                Layout.alignment: Qt.AlignHCenter
                visible: false
            }

            GridLayout {
                columns: 2
                rowSpacing: 15
                columnSpacing: 15
                Layout.fillWidth: true

                FormLabel {
                    text: "Username:"
                }

                CustomTextField {
                    id: usernameInput
                    placeholderText: ""
                    Layout.fillWidth: true
                    Layout.minimumWidth: 180
                }

                FormLabel {
                    text: "Password:"
                }

                CustomTextField {
                    id: passwordInput
                    placeholderText: ""
                    echoMode: TextInput.Password
                    Layout.fillWidth: true
                    Layout.minimumWidth: 180
                }

                FormLabel {
                    text: "Repeat password:"
                }

                CustomTextField {
                    id: repeatPasswordInput
                    placeholderText: ""
                    echoMode: TextInput.Password
                    Layout.fillWidth: true
                    Layout.minimumWidth: 180
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.leftMargin: 5
                spacing: 8

                property string pass: passwordInput.text
                property bool hasLen: pass.length >= 8
                property bool hasLower: /[a-z]/.test(pass)
                property bool hasUpper: /[A-Z]/.test(pass)
                property bool hasDigit: /\d/.test(pass)
                property bool isMatching: repeatPasswordInput.text.length > 0 && pass === repeatPasswordInput.text

                component ChecklistItem : RowLayout {
                    property string label: ""
                    property bool checked: false
                    spacing: 8

                    Rectangle {
                        width: 16
                        height: 16
                        radius: 4
                        color: parent.checked ? "#23a559" : "transparent"
                        border.color: parent.checked ? "#23a559" : "#313338"
                        border.width: 1

                        Text {
                            anchors.centerIn: parent
                            text: "✓"
                            color: "white"
                            font.pixelSize: 11
                            font.bold: true
                            visible: parent.checked
                        }
                    }

                    Text {
                        text: parent.label
                        color: parent.checked ? "#23a559" : "#949ba4"
                        font.pixelSize: 13
                    }
                }

                ChecklistItem {
                    label: "At least 8 characters"
                    checked: parent.hasLen
                }
                ChecklistItem {
                    label: "At least 1 lowercase letter"
                    checked: parent.hasLower
                }
                ChecklistItem {
                    label: "At least 1 uppercase letter"
                    checked: parent.hasUpper
                }
                ChecklistItem {
                    label: "At least 1 digit"
                    checked: parent.hasDigit
                }
                ChecklistItem {
                    label: "Passwords match"
                    checked: parent.isMatching
                }
            }

            Button {
                id: registerButton
                text: "Register"
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 120
                Layout.preferredHeight: 35
                Layout.topMargin: 5

                contentItem: Text {
                    text: registerButton.text
                    color: "white"
                    font.bold: true
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    radius: 8
                    color: registerButton.down ? "#112937" : (registerButton.hovered ? "#0F2C46" : "#1F4C66")
                }

                onClicked: {
                    if (typeof registrationViewBackend !== "undefined") {
                        registrationViewBackend.AttemptRegistration(usernameInput.text, passwordInput.text, repeatPasswordInput.text)
                    }
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 5

                FormLabel {
                    text: "Already have an account?"
                }

                FormLabel {
                    id: linkBackToLogin
                    text: "Log in"
                    color: loginMouseArea.pressed ? "#112937" : (loginMouseArea.containsMouse ? "#4aa3e5" : "#0078d7")
                    font.underline: loginMouseArea.containsMouse

                    MouseArea {
                        id: loginMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            if (typeof registrationViewBackend !== "undefined") {
                                registrationViewBackend.RequestNavigateToLogin()
                            }
                        }
                    }
                }
            }
        }

        Connections {
            target: typeof registrationViewBackend !== "undefined" ? registrationViewBackend : null

            function onRegistrationFailed(errorMessage) {
                errorTextLabel.text = errorMessage
                errorTextLabel.visible = true
            }
        }
    }
}