import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.12

ToolBar {
    id: toolBar
    property alias labelColor: toolRec.color;

    Rectangle {
        id: toolRec
        width: parent.width; height: parent.height
        anchors.bottom: parent.bottom
        color: "transparent"
    }

    RowLayout {
        id: row
        anchors.fill: parent
        ToolButton {
            text: qsTr("<<")
            onClicked: stack.pop()
        }
        Label {
            id: label
            Text {
                id: labelText
                anchors.centerIn: parent
                text: qsTr("Babel")
                color: "#EEEEEE"
                font.bold: true
                font.pixelSize: 28
            }
            elide: Label.ElideRight
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.  AlignVCenter
            Layout.fillWidth: true
        }
        ToolButton {
            text: qsTr("☰")
            onClicked: menu.open()
        }
    }
}
