import QtQuick 2.0

ListModel {
    id: contactModel

    function clearListElement() {
        clear();
    }

    function createListElement(name, friendId, status) {
        append({
            name: name,
            id: friendId,
            status: status
        });
    }

    function setMessage(id, msg) {
        for (var i = 0; i < contactModel.count; ++i) {
            if (id == contactModel.get(i).id) {
                contactModel.get(i).msg = msg;
                break;
            }
        }
    }

    function getElementById(id) {
        for (var i = 0; i < contactModel.count; ++i) {
            if (id == contactModel.get(i).id) {
                return contactModel.get(i);
            }
        }
        return null;
    }

    function getElementByName(friendName) {
        for (var i = 0; i < contactModel.count; ++i) {
            if (friendName == contactModel.get(i).name) {
                return contactModel.get(i);
            }
        }
        return null;
    }

    function getSize() {
        return contactModel.count;
    }
}