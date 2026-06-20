import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

Rectangle {
    color: "#1d1d1d"

    component FormLabel : Text {
        color: "white"
        font.pixelSize: 14
    }

    Item {
        id: formContainer
        anchors.centerIn: parent
        width: Math.min(450, parent.width - 60)
        height: Math.min(320, parent.height - 60)

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
            spacing: 25

            Text {
                text: "Login to Epsilon"
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
                    text: "Email:"
                }

                TextField {
                    id: emailInput
                    placeholderText: "example@epsilon.com"
                    Layout.fillWidth: true
                    Layout.minimumWidth: 180
                }

                FormLabel {
                    text: "Password:"
                }

                TextField {
                    id: passwordInput
                    placeholderText: "******"
                    echoMode: TextInput.Password
                    Layout.fillWidth: true
                    Layout.minimumWidth: 180
                }
            }

            Button {
                id: loginButton
                text: "Log in"
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 120
                Layout.preferredHeight: 35

                contentItem: Text {
                    text: loginButton.text
                    color: "white"
                    font.bold: true
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    radius: 8
                    color: loginButton.down ? "#112937" : (loginButton.hovered ? "#0F2C46" : "#1F4C66")
                }

                onClicked: {
                    loginViewBackend.AttemptLogin(emailInput.text, passwordInput.text)
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 5

                FormLabel {
                    text: "Don't have an account?"
                }

                FormLabel {
                    id: link_create_account
                    text: "Create account"
                    color: createAccountMouseArea.pressed ? "#112937" : (createAccountMouseArea.containsMouse ? "#4aa3e5" : "#0078d7")
                    font.underline: createAccountMouseArea.containsMouse

                    MouseArea {
                        id: createAccountMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }
        }
    }

    Popup {
        id: logoutSuccessPopup
        y: 40
        x: (parent.width - width) / 2
        padding: 12

        background: Rectangle {
            color: "#23a559"
            radius: 8
        }

        RowLayout {
            spacing: 8

            Item {
                width: 20
                height: 20

                Image {
                    id: checkIcon
                    source: "../../../../resources/check.svg"
                    anchors.fill: parent
                    sourceSize.width: 20
                    sourceSize.height: 20
                    visible: true
                }
            }

            Text {
                text: "Logged out successfully"
                color: "white"
                font.pixelSize: 14
                font.bold: true
            }
        }

        Timer {
            id: popupTimer
            interval: 3000
            onTriggered: logoutSuccessPopup.close()
        }

        onOpened: popupTimer.start()
    }

    Connections {
        target: typeof loginViewBackend !== "undefined" ? loginViewBackend : null

        function onLoginFailed(errorMessage) {
            errorTextLabel.text = errorMessage
            errorTextLabel.visible = true
        }

        function onLoginSucceeded() {
            errorTextLabel.visible = false
        }

        function onShowSuccessPopup() {
            logoutSuccessPopup.open()
        }
    }
}