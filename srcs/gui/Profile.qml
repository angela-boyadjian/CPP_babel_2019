import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12
import QtQuick.Dialogs 1.0

import "Components" as Cmp

Item {
    property string objType: "Profile"
    Component {
        id: headerComponent
        Rectangle {
            width: ListView.view.width
            height: 70
            color: "#EEEEEE"
            Text {
                font.family: "Arial"
                font.pointSize: 22
                font.bold: true
                smooth:true
                text: 'Personal Informations'
            }
        }
    }

    Rectangle {
        id: rectListView
        width: 400; height: 412
        color: "#EEEEEE"

        ListView {
            id: listView
            anchors.fill: parent
            anchors.margins: 40
            spacing: 50
            header: headerComponent
            model: ListModel {
                ListElement {
                    fieldName: "Firstname"
                    inputType: 0
                }
                ListElement {
                    fieldName: "Family name"
                    inputType: 0
                }
                ListElement {
                    fieldName: "Email"
                    inputType: 0
                }
            }
            delegate: items
        }

        Component {
            id: items

            Rectangle {
                id: rect
                width: ListView.view.width
                height: 30
                color: "#EEEEEE"
                Text {
                    font.family: "Arial"
                    font.pointSize: 14
                    smooth:true
                    text: fieldName + " : " + txtinput.getInputText()
                }
                Rectangle {
                    id: txtinput
                    width: 200
                    height: 30
                    function getInputText() { return txtField.text; }
                    anchors.top: rect.bottom
                    TextField {
                       id: txtField
                       Layout.fillWidth: true
                       color: "black"
                       hoverEnabled: true
                    }
                }
            }
        }
        Rectangle {
            id: rect
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 40
            width: 200
            height: 65
            color: "#EEEEEE"
            Text {
                font.family: "Arial"
                font.pointSize: 14
                smooth:true
                text: "Gender" + " : " + themeBox.displayText
            }
            ComboBox {
                id: themeBox
                width: 200
                anchors.bottom: parent.bottom
                model: ListModel {
                    id: model
                    ListElement { text: "Male" }
                    ListElement { text: "Female" }
                    ListElement { text: "Other" }
                }
                contentItem: Text {
                    leftPadding: 70
                    text: themeBox.displayText
                    font.pointSize: 12
                    font.bold: true
                    color: "black"
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
                background: Rectangle {
                    implicitWidth: 120
                    implicitHeight: 30
                    border.color: "black"
                    border.width: themeBox.visualFocus ? 2 : 1
                }
                delegate: ItemDelegate {
                    width: themeBox.width
                    contentItem: Text {
                        text: modelData
                        color: "steelblue"
                        font: themeBox.font
                        elide: Text.ElideRight
                        verticalAlignment: Text.AlignVCenter
                    }
                    highlighted: themeBox.highlightedIndex === index
                }
            }
        }
    }
    Rectangle {
        width: 300; height: 320
        anchors.right: parent.right
        anchors.rightMargin: 300
        anchors.top: parent.top
        anchors.topMargin: 50
        color: "#EEEEEE"
        
        Image {
            id: profilPic
            anchors.centerIn: parent
            width: 260; height: 260
            source: "qrc:/Images/profilPic"
            Button {
                width:100; height: 30
                anchors.bottom: parent.top
                anchors.left: parent.left
                anchors.leftMargin: (parent.width - width) / 2
                highlighted: true
                text: "browse"
                onClicked: fileDialog.visible = true
            }
        }

        Rectangle {
            id: userNameRect
            width: 300; height: 30
            anchors.top: profilPic.bottom
            color: "#EEEEEE"

            Text {
                anchors.centerIn: parent
                text: userProfile.getUserName()
                font.pixelSize: 22
            }
        }
    }
    FileDialog {
        id: fileDialog
        title: "Browse an image"
        folder: shortcuts.home
    }

    Rectangle {
        Text {
            anchors.bottom: parent.top
            text: "BIO"
            font.family: "Arial"
            font.pointSize: 14
            font.bold: true
            smooth:true

        }
        width: 450; height: 260
        border.width: 3
        border.color: "black"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60
        anchors.right: parent.right
        anchors.rightMargin: 215
        TextArea {
            anchors.left: parent.left
            anchors.leftMargin: 4
            selectByMouse: true
            width: parent.width - 18; height: parent.height
            text: ""
        }
    }

}