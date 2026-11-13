import QtQuick 2.0
import QtQuick.Controls 2.3
import "../../qml/"
Item {
    id: root
    width: 600
    height: 400

    signal sigLogin(string name, string passwd);
    signal sigExit();

    Configs_Res {
        id: cofig_Res
        lngType: LngMgr.curLngType()
    }

    Rectangle {
        id: rootRect
        width: parent.width
        height: parent.height
        color: "#F0F0F0"
    }

    Keys.onReturnPressed: {   // 回车
        console.log("Keys.onReturnPressed.")
        btn_ok.enter_activate()
    }

    Keys.onEnterPressed: {  // 小键盘的enter
        console.log("Keys.onEnterPressed.")
        btn_ok.enter_activate()
    }


    Label {
        id: titles
        x: 0
        y: 60
        font.pixelSize: 24;
        font.bold: true

        width: parent.width
        height: 30
        verticalAlignment: Text.AlignVCenter 	//垂直居中，控件必须有height才可以使用
        horizontalAlignment: Text.AlignHCenter 	//水平居中，控件必须有width才可以使用
        text: "趋盛科技板卡升级"
    }

    //![用户名]
    Item {
        id: user_name_item
        x: 110
        y: 150
        width: 380
        height: 40
        Label {
            id: usrname_title_id
            x: 0
            y: 0
            width: 120
            height: 30
            font.pixelSize: cofig_Res.font_Normal_Size;
            verticalAlignment: Text.AlignVCenter 	//垂直居中，控件必须有height才可以使用
            text: cofig_Res.ids_USER_NAME
        }

        Rectangle {
            width: 240
            height: 30
            anchors.left: usrname_title_id.right
            anchors.leftMargin: 20
            anchors.top: usrname_title_id.top

            border.color: name_textField.activeFocus ? "blue" : "black"
            border.width: name_textField.activeFocus ? 2 : 1

            TextField {
                id: name_textField
                anchors.fill: parent
                placeholderText: cofig_Res.ids_INPUT_NAME
                focus: true
            }
        }
    }

    //![密码]
    Item {
        id: passwd_item
        anchors.left: user_name_item.left
        anchors.top: user_name_item.bottom
        anchors.topMargin: 20
        width: 380
        height: 40
        Label {
            id: passwd_title_id
            x: 0
            y: 0
            width: 120
            height: 30
            font.pixelSize: cofig_Res.font_Normal_Size;
            verticalAlignment: Text.AlignVCenter 	//垂直居中，控件必须有height才可以使用
            text: cofig_Res.ids_PASSWORD
        }

        Rectangle {
            width: 240
            height: 30
            anchors.left: passwd_title_id.right
            anchors.leftMargin: 20
            anchors.top: passwd_item.top

            border.color: passwd_textField.activeFocus ? "blue" : "black"
            border.width: passwd_textField.activeFocus ? 2 : 1

            TextField {
                id: passwd_textField
                anchors.fill: parent
                passwordCharacter: "*"
                echoMode: TextField.Password
                placeholderText: cofig_Res.ids_INPUT_PASSWORD
            }
        }
    }

    Rectangle {
        id: warnnings_item
        width: parent.width
        height: 30
        anchors.top: passwd_item.bottom
        anchors.topMargin: 20
        visible: false
        color: rootRect.color
        Label {
            id: warnnings_txt
            x: 0
            width: parent.width
            height: parent.height
            text: LoginParent.logErMsg
            color: "red"

            verticalAlignment: Text.AlignVCenter 	//垂直居中，控件必须有height才可以使用
            horizontalAlignment: Text.AlignHCenter 	//水平居中，控件必须有width才可以使用
        }
    }

    Rectangle{
        id:key_rect11
    }

    //![按键-ok]
    Button {
        id: btn_ok
        anchors.left: passwd_item.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        width: 120
        height: 40
        hoverEnabled: true
        focus: true
        contentItem:  Text {
            width: parent.width
            height: parent.height
            font.pixelSize: cofig_Res.font_Normal_Size;
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            text: cofig_Res.ids_OK
            color: (btn_ok.down || btn_ok.hovered) ? "#17a81a" : "#FFFF"

        }


        onClicked: {
            if(!LoginParent.userLogin(name_textField.text, passwd_textField.text))
            {
                name_textField.text = "";
                passwd_textField.text = "";
                name_textField.focus = true

                warnnings_item.visible = true;
            }
        }

        function enter_activate() {
            console.debug("Button activated");
            btn_ok.clicked()
        }
    }


    //![按键-退出]
    Button {
        id: btn_exit
        anchors.right: passwd_item.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        width: 120
        height: 40
        hoverEnabled: true

        contentItem:  Text {
            width: parent.width
            height: parent.height
            font.pixelSize: cofig_Res.font_Normal_Size;
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            text: cofig_Res.ids_EXIT
            color: (btn_exit.down || btn_exit.hovered) ? "#17a81a" : "#FFFF"
        }

        onClicked: {
            sigExit();
        }
    }
}
