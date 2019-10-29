import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.12
import QtMultimedia 5.12

import babel.qt.worker 1.0
import babel.qt.contacts 1.0
import babel.qt.call 1.0

import "Components" as Cmp

Item {
    id: contactColumns
    objectName: "ContactObject"
    width: 1200; height:800

    ContactModel { id: cm }
    Worker { id: worker }
    Cmp.ErrPopUp { id: popUpError }

    signal clickedAccept()
    signal clickedDeny()

    Contacts {
        id: contacts
        onFriendListChanged: {
            cm.clearListElement();
            for (let i = 0; i < friendList.length; i++) {
                const param = friendList[i].split('.');
                cm.createListElement(param[0], param[1], param[2]);
            }
            if (cm.getSize() > 1 && cm.getElementById(2) != null) {
                let friend = cm.getElementById(2);
                topArea.centerText.text = friend.name;
                if (friend.status === "Offline") {
                    topArea.statusImg.source = "Images/offline.png";
                } else {
                    topArea.statusImg.source = "Images/online.png";
                }
                chat.target = 2;
            }
            topArea.cm = cm;
            chat.c_model = cm;
        }
    }

    Chat { id: chat }
    HomeTopArea { id: topArea }

    Rectangle {
        width: 400; height:800
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#90CAF9" }
            GradientStop { position: 1.0; color: "#d7d7d7" }
        }
    
        ListView {
            id: listView
            anchors.fill: parent
            anchors.margins: 10
            clip: true
            model: cm
            delegate: chosenItem
            spacing: 5
            header: headerComponent
            focus: true
            currentIndex: 0
        }
        Rectangle {
            id: addFriend
            width: 250; height: 48
            anchors.bottom: parent.bottom
            anchors.bottomMargin: height + 20
            anchors.right: parent.right
            anchors.rightMargin: ((parent.width - width) / 2) + ((48 + 10) / 2)

            color: "#FFCC80"
            border.color: "steelblue"
            border.width: 2
            radius: 10
            TextField {
                id: textFiedlAddFriend
                width: parent.width - 20
                anchors.centerIn: parent
                color: "black"
                Layout.fillWidth: true
                placeholderText: "Add new friend"
                hoverEnabled: true
            }
        }

        Rectangle {
            id: addButton
            anchors.left: addFriend.right
            anchors.leftMargin: 10
            anchors.bottom: addFriend.bottom
            width: 48; height: 48
            color: "#FFCC80"
            border.color: "steelblue"
            border.width: 2
            radius: 10

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                Image {
                    id: addFriendImg
                    anchors.centerIn: parent
                    width: 35; height: 35
                    source: "qrc:/Images/addFriend.png"
                    visible: true
                }
                onEntered: {
                    addButton.width = 53;
                    addButton.height = 53;
                    addFriendImg.width = 40;
                    addFriendImg.height = 40;
                }
                onExited: {
                    addButton.width = 48;
                    addButton.height = 48;
                    addFriendImg.width = 35;
                    addFriendImg.height = 35;
                }
                onClicked: {
                    let status = contacts.addFriend(textFiedlAddFriend.text);
                    if (status == "OK") {
                        textFiedlAddFriend.text = "";
                    } else {
                        popUpError.errorText = status;
                        popUpError.open();
                    }
                }
            }
        }

        Component {
            id: headerComponent

            Rectangle {
                width: ListView.view.width
                height: 20
                color: "#FFCC80"
                Text {
                    anchors.centerIn: parent
                    font.family: "Arial"
                    font.pointSize: 14
                    font.bold: true
                    smooth:true
                    text: 'Contacts'
                }
            }
        }
        Component {
            id: chosenItem
        
            Rectangle {
                id: rec
                width: ListView.view.width
                height: 40
                color: "#EF9A9A"
                border.color: Qt.lighter(color, 1.1)

                Text {
                    id: chosenItemText
                    color: "white"
                    font.family: "Arial"
                    font.pointSize: 14
                    font.bold: true
                    smooth:true
                    text: name
                    anchors.centerIn: parent
                }
                RoundButton {
                    id: myRoundButton
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 4
                    radius: 16
                    onClicked: textArea.readOnly = true
                    background: Rectangle {
                        radius: myRoundButton.radius
                        color: status == "Offline" ? "red" : "#A5D6A7"
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    anchors.rightMargin: 35
                    onClicked: {
                        if (status === "Offline") {
                            topArea.statusImg.source = "Images/offline.png"
                        } else {
                            topArea.statusImg.source = "Images/online.png"
                        }
                        topArea.centerText.text = name;
                        chat.target = cm.getElementByName(topArea.centerText.text).id;
                        ListView.currentIndex = index;
                    }
                }
                Rectangle {
                    id: trash
                    width: 30; height: 30
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5
                    color: "#FFCC80"
                    border.color: "steelblue"
                    radius: 8

                    Image {
                        anchors.centerIn: parent
                        width: 23; height: 23
                        source: "qrc:/Images/removeFriend.png"
                        visible: true
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: {
                            trash.border.color = "red"
                        }
                        onExited: {
                            trash.border.color = "steelblue"
                        }
                        onClicked: {
                            contacts.removeFriend(name);
                        }
                    }
                }
            }
        }
    }
}