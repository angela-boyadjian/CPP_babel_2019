import QtQuick 2.12
import QtQuick.Controls 2.12

Popup {
    id: popup

    property alias errorText: textPopUp.text

    leftMargin: (1200 - popUpRect.implicitWidth) / 2
    topMargin: ((800 - popUpRect.implicitHeight) / 2) - 100
    background: Rectangle {
        id: popUpRect
        color: "#d9dbd9"
        implicitWidth: 380
        implicitHeight: 200
        radius: 10
        border.color: "red"
        border.width: 8

        Text {
            id: textPopUp
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.left: parent.left
            anchors.leftMargin: (parent.implicitWidth - t_metrics.tightBoundingRect.width) / 2
            font.pixelSize: 23
            text: "Error"
        }

        Button {
            width: 110; height: 45
            highlighted: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: (parent.implicitWidth - width) / 2
            text: "OK"
            onClicked: { popup.close(); }
        }

        TextMetrics {
            id: t_metrics
            font: textPopUp.font
            text: textPopUp.text
        }
    }
}