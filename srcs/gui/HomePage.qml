import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.12

import "Components" as Cmp

Item {
    property string objType: "Home"
    width: 1200; height:800

    Image {
        anchors.centerIn: parent
        source: "qrc:/Images/home_background.jpg"
    }

    ContactsColumn {}
}