import QtQuick 2.0

Item {
    property string begLngType: "zh_CN"
    property string lngType : "zh_CN"

    property string ids_USER_NAME: lngType === begLngType ? LngMgr.trs("IDS_USER_NAME") : LngMgr.trs("IDS_USER_NAME")
    property string ids_INPUT_NAME: lngType === begLngType ? LngMgr.trs("IDS_INPUT_NAME") : LngMgr.trs("IDS_INPUT_NAME")
    property string ids_PASSWORD: lngType === begLngType ? LngMgr.trs("IDS_PASSWORD") : LngMgr.trs("IDS_PASSWORD")
    property string ids_INPUT_PASSWORD: lngType === begLngType ? LngMgr.trs("IDS_INPUT_PASSWD") : LngMgr.trs("IDS_INPUT_PASSWD")
    property string ids_USERNAME_ERROR: lngType === begLngType ? LngMgr.trs("IDS_USERNAME_ERROR") : LngMgr.trs("IDS_USERNAME_ERROR")
    property string ids_PASSWORD_ERROR: lngType === begLngType ? LngMgr.trs("IDS_PASSWORD_ERROR") : LngMgr.trs("IDS_PASSWORD_ERROR")
    property string ids_LOGIN: lngType === begLngType ? LngMgr.trs("IDS_LOGIN") : LngMgr.trs("IDS_LOGIN")
    property string ids_OK: lngType === begLngType ? LngMgr.trs("IDS_OK") : LngMgr.trs("IDS_OK")
    property string ids_EXIT: lngType === begLngType ? LngMgr.trs("IDS_EXIT") : LngMgr.trs("IDS_EXIT")


    /******************************************************** 多语言资源  END *****************************************************************************/


    /******************************************************** 字体资源 Start ***************************************************************************/

    property string font_Family : lngType === begLngType ? UiStyleMgr.getFontFamily() : UiStyleMgr.getFontFamily()
    property string font_NormalColor :  "#DCDDE0"
//    property string font_HightLightColor :  UiStyleMgr.getHightLightFontColor()
    property int font_Normal_Size: UiStyleMgr.getButtonFontSize()
    property int font_Big_Size : UiStyleMgr.getBigTitleFontSize()
}
