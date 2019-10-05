import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12

import babel.qt.login 1.0

import "Components" as Cmp

Item {
    Cmp.ErrPopUp { id: popUpError }
    Rectangle {
        Login { id: loginObj }
        width: 1200; height: 800
        color: "teal"

        Text {
            x: 450; y: 20
            text: qsTr("Welcome !")
            font.pixelSize: 60
            font.bold: true
            color: "white"
        }

        Image {
            x: 510; y: 120;
            width: 150; height: 150
            source: "qrc:/Images/rocket.png"
        }

        ColumnLayout {
            anchors.centerIn: parent
            anchors.margins: 10
            spacing: 10
            width: 300; height: 150
            TextField {
                id: login
                color: "white"
                Layout.fillWidth: true
                placeholderText: "Username"
                hoverEnabled: true
            }

            TextField {
                id: password
                Layout.fillWidth: true
                color: "white"
                placeholderText: "Password"
                echoMode: TextInput.Password
                hoverEnabled: true
            }

            TextField {
                id: address
                color: "white"
                Layout.fillWidth: true
                placeholderText: "Hostname"
                hoverEnabled: true
            }
        }

        Button {
            id: button
            x: 475; y: 500;
            width: 250; height: 50
            highlighted: true
            text: "Connect"
            onClicked: {
                let status = loginObj.sign(login.text, password.text, address.text);
                if (status == false) {
                    popUpError.errorText = "Failed to login";
                    popUpError.open();
                } else {
                    load_page("Home");
                }
            }
        }
    }
}