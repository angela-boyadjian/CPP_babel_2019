import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12

ComboBox {
    id: themeBox
    width: 200
    model: ListModel {
        id: model
        ListElement { text: "Default" }
        ListElement { text: "Candies" }
        ListElement { text: "Darker" }
    }
    contentItem: Text {
        leftPadding: 70
        text: themeBox.displayText
        font.pointSize: 12
        font.bold: true
        color: "white"
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 120
        implicitHeight: 40
        border.color: "#80CBC4"
        color: "#80CBC4"
        border.width: themeBox.visualFocus ? 2 : 1
        radius: 10
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
    
    onAccepted: {
        if (find(editText) === -1)
            model.append({text: editText})
    }
}
