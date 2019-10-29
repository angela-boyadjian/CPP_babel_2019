import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12

import babel.qt.login 1.0

import "Components" as Cmp

Item {
    property string objType: "Login"
    Cmp.ErrPopUp { id: popUpError }
    Login { id: loginObj }
    
    function isLogged() {
        return loginObj.getLoginStatus();
    }

    Rectangle {
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
            id: connectButton
            x: 380; y: 500;
            width: 215; height: 50
            highlighted: true
            text: "Connect"
            onClicked: {
                let status = loginObj.connect(login.text, password.text, address.text);
                if (status != "OK") {
                    popUpError.errorText = status;
                    popUpError.open();
                } else {
                    userProfile.setConnected(true)
                    userProfile.setUserName(login.text)
                    load_page("Home");
                }
            }
        }
        Button {
            id: signUpButton
            x: 615; y: 500;
            width: 215; height: 50
            highlighted: true
            text: "Sign up"
            
            onClicked: {
                let status = loginObj.signUp(login.text, password.text, address.text);
                if (status == "OK") {
                    userProfile.setConnected(true)
                    userProfile.setUserName(login.text)
                    load_page("Home");
                } else {
                    popUpError.errorText = "Failed to login";
                    popUpError.open();
                }
            }
        }
    }
}