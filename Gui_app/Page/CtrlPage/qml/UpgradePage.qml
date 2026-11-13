import QtQuick 2.0
import QtQuick.Layouts 1.1
import "../../../qml/"

Item {
    id: root
    x: 0
    y: 0
    width: 150
    height: 650
    property int sel_index: 0
    property int mouseEntered: -1

    signal sigSwitchPage(int pgId)

    Configs_Res {
        id: user_Res
        lng: LngMgr.curLngType()
    }

    Rectangle {
        anchors.fill:  parent
        color: user_Res.parent_bg_color
    }

    ColumnLayout {
        spacing: 2

        Rectangle {
            id: upgrade_bt
            Layout.alignment: Qt.AlignLeft
            width: 150
            height: 40

            gradient: Gradient {
                GradientStop {
                    position:  0.0
                    color:  (0 === mouseEntered) ? (user_Res.ent_upColor) :  (0 !== sel_index ? user_Res.nor_upColor : user_Res.sle_upColor)
                }
                GradientStop {
                    position:  0.5
                    color: (0 === mouseEntered) ? (user_Res.ent_midColor) : (0 !== sel_index ? user_Res.nor_midColor : user_Res.sle_midColor)
                }
                GradientStop {
                    position:  1.0
                    color: (0 === mouseEntered) ? (user_Res.ent_dwColor) : (0 !== sel_index ? user_Res.nor_dwColor : user_Res.sle_dwColor)
                }
            }

            Text {
                anchors.centerIn: parent
                text: user_Res.ids_Upgrade
                font.family:  user_Res.font_family
                font.pixelSize: user_Res.font_NormalSize
                color: user_Res.font_Color
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    console.log("Mouse Enter Upgrade menu.")
                    mouseEntered = 0
                }

                onExited: {
                    console.log("Mouse Exited Upgrade menu.")
                    mouseEntered = -1
                }

                onClicked: {
                    sel_index = 0
                    sigSwitchPage(sel_index)
                }
            }
        }

        Rectangle {
            id: setting_bt
            Layout.alignment: Qt.AlignLeft
            width: 150
            height: 40
            gradient: Gradient {
                GradientStop {
                    position:  0.0
                    color:  (1 === mouseEntered) ? (user_Res.ent_upColor) :  (1 !== sel_index ? user_Res.nor_upColor : user_Res.sle_upColor)
                }
                GradientStop {
                    position:  0.5
                    color: (1 === mouseEntered) ? (user_Res.ent_midColor) : (1 !== sel_index ? user_Res.nor_midColor : user_Res.sle_midColor)
                }
                GradientStop {
                    position:  1.0
                    color: (1 === mouseEntered) ? (user_Res.ent_dwColor) : (1 !== sel_index ? user_Res.nor_dwColor : user_Res.sle_dwColor)
                }
            }

            Text {
                anchors.centerIn: parent
                text: user_Res.ids_Setting
                font.family:  user_Res.font_family
                font.pixelSize: user_Res.font_NormalSize
                color: user_Res.font_Color
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    console.log("Mouse Enter Setting menu.")
                    mouseEntered = 1
                }

                onExited: {
                    console.log("Mouse Exited Setting menu.")
                    mouseEntered = -1
                }

                onClicked: {
                    sel_index = 1
                    sigSwitchPage(sel_index)
                }
            }
        }
    }
}

