import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12

import "Components" as Cmp

Item {
    GridView {
        id: mygridview
        cellWidth: 100
        cellHeight: 300
        anchors.fill: parent
        model: ListModel {
            ListElement {
                name: 'Home'
            }
            ListElement {
                name: 'Contacts'
            }
        }
    
        delegate: Button {
            id: mybutton
            width: 100
            height: 50
            highlighted: true
            text: name
            onClicked: {
                load_page(name)
            }
        }
    }
}