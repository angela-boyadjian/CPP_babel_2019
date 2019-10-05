import QtQuick 2.0

ListModel {
    id: msgModel

    function createListElement(msg) {
        insert(0, {
            message: msg
        });
    }

}