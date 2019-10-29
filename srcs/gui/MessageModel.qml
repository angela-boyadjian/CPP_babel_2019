import QtQuick 2.0

ListModel {
    id: msgModel

    function createListElement(msg, me, name) {
        insert(0, {
            message: msg,
            sentByMe: me,
            friendName: name
        });
    }

    function delLastElem() {
        remove(msgModel.count - 1);
    }

    function getSize() {
        return msgModel.count;
    }
}