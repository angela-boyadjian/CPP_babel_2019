import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.12

import "Components" as Cmp

Pane {
    id: chatPane

    property alias sendButton: sendButton
    property alias messageField: messageField

    Layout.fillWidth: true

    RowLayout {
        width: parent.width

        Rectangle {
            id: compose
            width: 700; height: 48
            color: "#EEEEEE"
            border.color: "steelblue"
            border.width: 2
            radius: 10
            
            TextArea {
                x: parent.x + 10
                id: messageField
                width: compose.width - 50;
                placeholderText: qsTr("Compose message")
                wrapMode: TextArea.Wrap
                hoverEnabled: true
            }
        }

        Button {
            id: sendButton
            text: qsTr("Send")
            enabled: messageField.length > 0
            focus: true
        }
    }
}