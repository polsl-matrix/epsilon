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
                    position: 0.0; color: "#2a2a2a"
                }
                GradientStop {
                    position: 1.0; color: "#373737"
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
}