import QtQuick 2.0

ListModel {
    id: contactModel

    function clearListElement() {
        clear();
    }

    function createListElement(name, friendId) {
        append({
            name: name,
            id: friendId,
            status: "Online"
        });
    }

    function getElementName(id) {
        for (var i = 0; i < contactModel.count; ++i) {
            if (id == contactModel.get(i).id) {
                return contactModel.get(i);
            }
        }
        return null;
    }
}