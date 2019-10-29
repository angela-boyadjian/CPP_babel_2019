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
    property ListModel cm

    property alias centerText: centerText
    property alias callImg: callImg
    property alias hangupImg: hangupImg
    property alias statusImg: statusImg

    Audio {
        id: incomingCall
        loops: 1
        source: "qrc:/Sounds/incomingCall.mp3"
    }

    Audio {
        id: calling
        loops: 1
        source: "qrc:/Sounds/calling.mp3"
    }

    CallRequest {
        id: callPopup
        acceptButton.onClicked: {
            contactColumns.clickedAccept();
            close();
            incomingCall.stop();
        }
        denyButton.onClicked: {
            contactColumns.clickedDeny();
            close();
            incomingCall.stop();
        }
    }

    Call {
        id: callObj
        onCallingYou: {
            callPopup.open();
            callPopup.popupName = cm && cm.getElementById(callerId) ? cm.getElementById(callerId).name : "Alien";
            incomingCall.play();
        }
        onAcceptedYourCall: { calling.stop(); }
        onDeniedYourCall: {
            calling.stop();
            hangupImg.visible = false;
            callImg.visible = true;
        }
    }

    Text {
        id: centerText
        x: statusImg.x + 50; y: -50
        topPadding: 90
        color: "steelblue"
        font.family: "Arial"
        font.pointSize: 25;
        font.bold: true
        smooth:true
        visible: true
    }

    Image {
        id: statusImg
        x: 450; y: 50
        width: 20; height: 20
        source: "qrc:/Images/online.png"
    }

    Image {
        id: hangupImg
        x: centerText.x + 495; y: 28
        width: 60; height: 60
        source: "qrc:/Images/hangup.png"
        visible: false
        MouseArea {
            anchors.fill: parent
            onClicked: {
                callObj.stopCall();
                hangupImg.visible = false;
                callImg.visible = true;

            }
        }
    }

    Image {
        id: callImg
        x: centerText.x + 500; y: 30
        width: 50; height: 50
        source: "qrc:/Images/phone.png"
        visible: true
        MouseArea {
            anchors.fill: parent
            onClicked: {
                let friends = cm.getElementByName(centerText.text);
                if (friends.status === "Offline") {
                    popUpError.errorText = "Friend's offline";
                    popUpError.open();
                } else {
                    callObj.requestCall(centerText.text);
                    calling.play();
                    callImg.visible = false;
                    hangupImg.visible = true;
                }
            }
        }
    }

    Image {
        id: videoImg
        x: callImg.x + 100; y: 30
        width: 50; height: 50
        source: "qrc:/Images/video.png"
        visible: true
    }
}