import QtQuick 2.0

Item {
    id: button

    property alias cellColor: rectangle.color

    x: 100; y: 100
    width: 40; height: 25

    Rectangle {
        id: rectangle
        border.color: "white"
        anchors.fill: parent
    }

    MouseArea {
        id: rani
        anchors.fill: parent
    }

    states: State {
        name: "pressed"; when: rani.pressed == true
        PropertyChanges { target: button; cellColor: "lightgreen" }
    }
}