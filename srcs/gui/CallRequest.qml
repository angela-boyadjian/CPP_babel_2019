import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.12

import "Components" as Cmp

Popup {
    id: popup
    x: 450; y: 100
    width: 500
    height: 500
    modal: true
    focus: true

    property alias popupName: textName.textContent
    property alias acceptButton: acceptButton
    property alias denyButton: denyButton

    Image {
        anchors.horizontalCenter: parent.horizontalCenter
        width: 80; height: 80
        source: "qrc:/Images/phone.png"
    }

    Cmp.Text {
        x: parent.x + 110; y: parent.y + 100
        textSize: 30
        textContent: "Incoming call from:"
        textColor: "steelblue"
        fontBold: false
    }
    Cmp.Text {
        id: textName
        y: 200
        textSize: 30
        textContent: "Rani"
        textColor: "steelblue"
    }
    Button {
        id: acceptButton
        width: 150; height: 100
        x: parent.x + 40; y: parent.y + 350
        highlighted: true
        text: "Accept call"
        visible: true
        background: Rectangle { color: "#4CAF50" }
    }
    Button {
        id: denyButton
        width: 150; height: 100
        x: parent.x + 280; y: parent.y + 350
        highlighted: true
        text: "Deny call"
        visible: true
        background: Rectangle { color: "#990000" }
    }
    closePolicy: Popup.CloseOnEscape
}