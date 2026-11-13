import QtQuick 2.0
import QtQuick.Layouts 1.1

Item {
    id: root
    x: 0
    y: 0
    width: 578
    height: 379
    property int sel_index: 0
    property int mouseEntered: -1


    CommonWiget_Res {
        id: common_Res
        lng: LngMgr.curLngType()
    }


    Rectangle {
        anchors.fill:  parent
        color: common_Res.parent_bg_color
    }

    Rectangle {
        id: product
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 10
        width: parent.width
        height: 30
        color: common_Res.parent_bg_color
        Text {
            anchors.fill: parent

            font.family:  common_Res.font_family
            font.pixelSize: common_Res.font_NormalSize
            color: common_Res.font_Color
            verticalAlignment: Text.AlignVCenter 	//垂直居中，控件必须有height才可以使用
            horizontalAlignment: Text.left

            text: "趋盛科技公司板卡升级工具."
        }
    }

    Rectangle {
        id: version
        anchors.left: product.left
        anchors.top: product.top
        anchors.topMargin: 40
        width: parent.width
        height: 30
        color: common_Res.parent_bg_color
        Text {
            anchors.fill: parent

            font.family:  common_Res.font_family
            font.pixelSize: common_Res.font_NormalSize
            color: common_Res.font_Color
            verticalAlignment: Text.AlignVCenter 	//垂直居中，控件必须有height才可以使用
            horizontalAlignment: Text.left

            text: "版本: " + AboutPage.proVersion
        }
    }

    Rectangle {
        id: title
        anchors.left: version.left
        anchors.top: version.top
        anchors.topMargin: 50
        width: parent.width
        height: 30
        color: common_Res.parent_bg_color
        Text {
            anchors.fill: parent

            font.family:  common_Res.font_family
            font.pixelSize: common_Res.font_NormalSize
            color: common_Res.font_Color
            verticalAlignment: Text.AlignVCenter 	//垂直居中，控件必须有height才可以使用
            horizontalAlignment: Text.left

            text: "Copyright(c)2025 Trendwin Technology Ltd. \n All Rights Reserved."
        }
    }
}
