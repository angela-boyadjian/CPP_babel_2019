import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12

import babel.qt.settings 1.0

import "Components" as Cmp

Item {
    property string objType: "Setting"
    Settings { id: settingsObj }

    Settings {
        id: settings
        property alias volume: volumeSlider.value
        property alias theme: themeBox.displayText
    }

    Rectangle {
        width: 1200; height: 800
        color: "#ffeecc"
        SwipeView {
            id: settingsSwipe

            anchors.fill: parent
            Item {
                id: settingsPage
            
                Cmp.Text {
                    textX: 500; textY: 50
                    textSize: 40
                    textContent: "Settings"
                    textColor: "steelblue"
                }

                Cmp.Text {
                    id: saveText
                    textX: 500; textY: 558
                    textContent: "Settings saved"
                    textColor: "#607D8B"
                    textVisible: false
                    fontBold: true
                }

                Button {
                    id: saveButton
                    width: 200; height: 50
                    x: 500; y: 600
                    highlighted: true
                    text: "Save"
                    onClicked: {
                        saveText.textVisible = true;
                        settingsObj.save(settings.volume, settings.theme);
                        headerBar.labelColor = settingsObj.getTheme();
                    }
                }
                Button {
                    id: resetButton
                    width: 200; height: 50
                    x: 980; y: 700
                    highlighted: true
                    text: "Reset"
                    onClicked: {
                        settingsObj.reset();
                        headerBar.labelColor = settingsObj.getTheme();
                        volumeSlider.value = settingsObj.getVolume();
                    }
                }
                
                Column {
                    x: 500; y: 200
                    spacing: 30

                    Image {
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: "qrc:/Images/artist.png"
                        width: 60; height: 60
                    }
                    Theme { id:themeBox }

                    Image {
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: "qrc:/Images/sound.png"
                        width: 50; height: 50
                        visible: volumeSlider.value > 0 ? true : false
                    }
                    Image {
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: "qrc:/Images/mute.png"
                        width: 50; height: 50
                        visible: volumeSlider.value > 0 ? false : true
                    }
                    Slider {
                        id: volumeSlider
                        anchors.horizontalCenter: parent.horizontalCenter
                        from: 0
                        to: 100
                        stepSize: 1
                        value: settingsObj.getVolume()
                    }
                }
            }
        }
    }
}