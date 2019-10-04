import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.12

import "Components" as Cmp

Item {
    id: chatItem
    width: 800; height: 700
    x: 400; y: 50

    property string inConversationWith

    Label {
        id: pageTitle
        text: inConversationWith
        font.pixelSize: 20
        anchors.centerIn: parent
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: pane.leftPadding + messageField.leftPadding
            displayMarginBeginning: 40
            displayMarginEnd: 40
            verticalLayoutDirection: ListView.BottomToTop
            spacing: 12
            model: 20
            delegate: Column {
                anchors.right: sentByMe ? parent.right : undefined
                spacing: 6

                readonly property bool sentByMe: model.recipient !== "Me"

                Row {
                    id: messageRow
                    spacing: 6
                    anchors.right: sentByMe ? parent.right : undefined

                    Rectangle {
                        width: Math.min(messageText.implicitWidth + 24,
                            listView.width - (!sentByMe ? avatar.width + messageRow.spacing : 0))
                        height: messageText.implicitHeight + 24
                        color: sentByMe ? "lightgrey" : "steelblue"

                        Label {
                            id: messageText
                            // text: model.message
                            text: "I am chatting!"
                            color: sentByMe ? "black" : "white"
                            anchors.fill: parent
                            anchors.margins: 12
                            wrapMode: Label.Wrap
                        }
                    }
                }

                Label {
                    id: timestampText
                    text: Qt.formatDateTime(model.timestamp, "d MMM hh:mm")
                    color: "lightgrey"
                    anchors.right: sentByMe ? parent.right : undefined
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
                    id: addFriend
                    width: 700; height: 48
                    color: "#EEEEEE"
                    border.color: "steelblue"
                    border.width: 2
                    radius: 10
                    
                    TextArea {
                        x: parent.x + 10
                        id: messageField
                        width: addFriend.width - 50;
                        placeholderText: qsTr("Compose message")
                        wrapMode: TextArea.Wrap
                        hoverEnabled: true
                    }
                }

                Button {
                    id: sendButton
                    text: qsTr("Send")
                    enabled: messageField.length > 0
                }
            }
        }
    }
}