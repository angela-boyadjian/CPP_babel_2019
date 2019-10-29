import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.12

import babel.qt.profil 1.0

import "Components" as Cmp

ApplicationWindow {
    id: main
    visible: true
    width: 1200
    height: 800
    title: qsTr("Tabs")

    Profil { id: pro }

    property alias headerBar:  bar
    property alias userProfile: pro

    Material.theme: Material.Dark
    Material.accent: Material.Violet
    Material.background: Material.Violet
    Material.foreground: Material.Violet

    header: HeaderBar { id: bar }
    Cmp.ErrPopUp {id: popUpError }

    Menu {
        id: menu
        x: 1000
        MenuItem {
            text: "Home"
            Component {
                id: homePage
                HomePage {}
            }
            onClicked: {
                if (userProfile.isConnected() == true) {
                    load_page("Home");
                } else {
                    popUpError.errorText = "You are not logged";
                    popUpError.open();
                }
            }
        }

        MenuItem {
            text: "Profile"
            Component {
                id: profilePage
                Profile {}
            }
            onClicked: {
                if (userProfile.isConnected() == true) {
                    load_page("Profile");
                } else {
                    popUpError.errorText = "You are not logged";
                    popUpError.open();
                }
            }
        }

        MenuItem {
            text: "Settings"
            Component {
                id: settingsPage
                Settings {}
            }
            onClicked: { load_page("Settings") }
        }
     
        MenuItem {
            text: "Logout"
            Component {
                id: loginPage
                LoginPage {}
            }
        }

        MenuItem {
            text: "Exit"
            onClicked: Qt.quit()
        }
    }

    StackView {
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            top: parent.top
        }
        id: stack
        initialItem: loginPage
    }

    function load_page(page) {
        switch (page) {
            case 'Login':
                let itemLog = stack.find(function(item, index) {
                    if (item.objType == "Login") {
                        let tmp = stack.pop(item)
                        stack.push(item);
                        return item;
                    } else {
                        return false;
                    }
                });
                if (itemLog == null) {
                    stack.push(loginPage);                
                }
                break;
            case 'Home':
                let itemHome = stack.find(function(item, index) {
                    if (item.objType == "Home") {
                        let tmp = stack.pop(item)
                        stack.push(item);
                        return item;
                    } else {
                        return false;
                    }
                });
                if (itemHome == null) {
                    stack.push(homePage);                    
                }
                break;
            case 'Profile':
                let itemProf = stack.find(function(item, index) {
                    if (item.objType == "Profile") {
                        let tmp = stack.pop(item)
                        stack.push(item);
                        return item;
                    } else {
                        return false;
                    }
                });
                if (itemProf == null) {
                    stack.push(profilePage);
                }
                break;
            case 'Settings':
                let itemSett = stack.find(function(item, index) {
                    if (item.objType == "Setting") {
                        let tmp = stack.pop(item)
                        stack.push(item);
                        return item;
                    } else {
                        return false;
                    }
                });
                if (itemSett == null) {
                    stack.push(settingsPage);
                }
                break;
        }
    }
}