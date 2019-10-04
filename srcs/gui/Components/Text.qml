import QtQuick 2.0

Item {
    id: textArea

    property alias textX: content.x
    property alias textY: content.y
    property alias textContent: content.text
    property alias textColor: content.color
    property alias textSize: content.font.pointSize
    property alias fontBold: content.font.bold
    property alias textVisible: content.visible

    Text {
        id: content
        width: 196; height: 62
        color: "#EF9A9A"
        font.family: "Arial"
        horizontalAlignment: Text.AlignHCenter
        smooth:true
        font.pointSize: 14
        font.bold: true
    }
}