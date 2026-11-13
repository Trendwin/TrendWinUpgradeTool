import QtQuick 2.0

Item {

    property  string lng: "zh_CN"


    /**************** UI资料路径 ****************************************/

    /******************背景颜色*****************************************/
    property string parent_bg_color: "#F0F0F0"
    property string nor_upColor: "#D8CBFF"
    property string nor_midColor: "#D49AFF"
    property string nor_dwColor: "#D8CBFF"

    property string ent_upColor: "#E8E8E8"
    property string ent_midColor: "#E8E8E8"
    property string ent_dwColor: "#E8E8E8"

    property string sle_upColor: "#C7C7C7"
    property string sle_midColor: "#C7C7C7"
    property string sle_dwColor: "#C7C7C7"

    /******************* 字体 *****************************************/
    property string font_family: (lng === "zh_CN") ? UiStyleMgr.getFontFamily() : UiStyleMgr.getFontFamily()
    property string font_NormalSize: (lng === "zh_CN") ? UiStyleMgr.getMenuFontSize() : UiStyleMgr.getMenuFontSize()
    property string font_Color: (lng === "zh_CN") ? UiStyleMgr.getFontColor() : UiStyleMgr.getFontColor()
    /****************** 多语言 ****************************************/

    property string ids_Upgrade: (lng === "zh_CN") ? LngMgr.trs("IDS_UPGRADE") : LngMgr.trs("IDS_UPGRADE")
    property string ids_Setting: (lng === "zh_CN") ? LngMgr.trs("IDS_Setting") : LngMgr.trs("IDS_Setting")
    property string ids_About: (lng === "zh_CN") ? LngMgr.trs("IDS_ABOUT") : LngMgr.trs("IDS_ABOUT")
}
