import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.12

import "Components" as Cmp

ApplicationWindow {
    id: main
    visible: true
    width: 1200
    height: 800
    title: qsTr("Tabs")

    property alias headerBar:  bar
    // property alias msgObj: msgObj

    Material.theme: Material.Dark
    Material.accent: Material.Violet
    Material.background: Material.Violet
    Material.foreground: Material.Violet

    header: HeaderBar { id: bar }

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
                // TODO Check if user is logged first
                load_page("Home")
            }
        }

        MenuItem {
            text: "Profile"
            Component {
                id: profilePage
                Profile {}
            }
            onClicked: load_page("Profile")
        }


        MenuItem {
            text: "Settings"
            Component {
                id: settingsPage
                Settings {}
            }
            onClicked: load_page("Settings")
        }

        MenuItem {
            text: "Logout"
            Component {
                id: loginPage
                LoginPage {}
            }
            onClicked: load_page("Login")
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
                stack.push(loginPage);
                break;
            case 'Home':
                stack.push(homePage);
                break;
            case 'Profile':
                stack.push(profilePage);
                break;
            case 'Settings':
                stack.push(settingsPage);
                break;
        }
    }
}