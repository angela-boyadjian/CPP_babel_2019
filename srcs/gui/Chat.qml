import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.12

import babel.qt.messager 1.0

import "Components" as Cmp

Item {
    id: chatItem
    width: 800; height: 700
    x: 400; y: 50

    property bool sentByMe: false
    property int target

    MessageModel {
        id: m_model
    }

    Messager {
        id: msgObj;
        onReceivedMessage: {
            m_model.createListElement(msg);
            senderId == 1 ? sentByMe = true : sentByMe = false;
        }
    }

    ColumnLayout {
        id: col
        anchors.fill: parent
        ListView {
            id: l
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: pane.leftPadding + messageField.leftPadding
            displayMarginBeginning: 40
            displayMarginEnd: 40
            verticalLayoutDirection: ListView.BottomToTop
            spacing: 12
            model: m_model
            delegate: Column {
                anchors.right: sentByMe ? parent.right : undefined
                spacing: 6

                Row {
                    id: messageRow
                    spacing: 6
                    anchors.right: chatItem.sentByMe ? parent.right : undefined

                    Rectangle {
                        width: Math.min(messageText.implicitWidth + 24,
                            listView.width - (!chatItem.sentByMe ? messageRow.spacing : 0))
                        height: messageText.implicitHeight + 24
                        color: chatItem.sentByMe ? "steelblue" : "lightgrey"

                        Label {
                            id: messageText
                            text: message
                            color: chatItem.sentByMe ? "white" : "black"
                            anchors.fill: parent
                            anchors.margins: 12
                            wrapMode: Label.Wrap
                        }
                    }
                }
            }
            ScrollBar.vertical: ScrollBar {}
        }
        Pane {
            id: pane
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
                    onClicked: {
                        onClicked: {
                            msgObj.sendMessage(messageField.text, chatItem.target);
                            chatItem.sentByMe = true;
                            m_model.createListElement(messageField.text);
                            messageField.text = "";
                        }
                    }
                }
            }
        }
    }
}