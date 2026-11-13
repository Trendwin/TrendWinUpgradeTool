import QtQuick 2.0
import QtQuick.Controls 2.0
Item {
    id: root
    width: 500
    height: 1000

    signal sigFinished()

    Rectangle {
        anchors.fill: parent
        color: "#6674FF"
    }

    Text {
        id: dd_t
        x: 50
        y: 50
        text: "this is micro setting page"
    }

    Button {
        id: real_ctrl_return_home_bt
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.bottom: parent.Bottom
        anchors.bottomMargin: 10
        width: 90
        height: 30
        text: "Return"

        onClicked: {
            visible: false
            sigFinished()
        }
    }
}
