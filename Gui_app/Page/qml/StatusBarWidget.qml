import QtQuick 2.0


Item {
    id: root
    x: 0
    y: 0
    Rectangle {
        anchors.fill : parent
        color: "#DBD7D5";
    }

    Text {
        id: tips
        anchors.left:  parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        text: StatusBarObj.comStatus
    }

}
