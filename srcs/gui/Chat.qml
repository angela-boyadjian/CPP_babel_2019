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

    property int target
    property ListModel c_model

    MessageModel { id: m_model }
    Cmp.ErrPopUp { id: popUpError }

    Messager {
        id: msgObj;
        onReceivedMessage: {
            if (chatItem.c_model != null) {
                if (m_model.getSize() >= 10) {
                    m_model.delLastElem();
                }
                let friend = chatItem.c_model.getElementById(senderId);
                m_model.createListElement(msg, false, friend.name);
            } else {
                m_model.createListElement(msg, false, "?");
            }
        }
    }

    ColumnLayout {
        id: col
        anchors.fill: parent
        ListView {
            id: l
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: chatPane.leftPadding + chatPane.messageField.leftPadding
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
                    anchors.right: sentByMe ? parent.right : undefined
                    Text {
                        id: senderName
                        x: messageText.x - 20 ; y: messageText.y
                        width: height; height: parent.height
                        text: friendName == "author" ? " " :  friendName 
                        color: "grey"
                        visible: !sentByMe
                    }
                    Rectangle {
                        width: Math.min(messageText.implicitWidth + 24,
                            listView.width - (sentByMe ? messageRow.spacing : 0))
                        height: messageText.implicitHeight + 24
                        color: sentByMe ? "steelblue" : "lightgrey"
                        Label {
                            id: messageText
                            text: message
                            color: sentByMe ? "white" : "black"
                            anchors.fill: parent
                            anchors.margins: 12
                            wrapMode: Label.Wrap
                        }
                    }
                }
            }
            ScrollBar.vertical: ScrollBar {}
        }
        function sendMsg() {
            if (c_model == null) {
                return;
            }
            let friend = c_model.getElementById(chatItem.target);
            if (friend.status === "Offline") {
                popUpError.errorText = "Friend's offline";
                popUpError.open();
                return;
            }
            msgObj.sendMessage(chatPane.messageField.text, chatItem.target);
            if (m_model.getSize() >= 10) {
                    m_model.delLastElem();
            }
            m_model.createListElement(chatPane.messageField.text, true, "author");
            chatPane.messageField.text = "";
        }
        ChatPane {
            id: chatPane
            sendButton.onClicked: col.sendMsg()
        }
    }
}