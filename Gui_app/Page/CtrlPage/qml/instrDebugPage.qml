import QtQuick 2.0

Item {
    id: root
    x: 0
    y: 0
    width: 150
    height: 1000

    Item {
        id: motor_id
        x: 20
        y: 20
        width: parent.width
        height: 50

        Rectangle {
            anchors.fill:  parent
            color: "green"
        }

    }
}
