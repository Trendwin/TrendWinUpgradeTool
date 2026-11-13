QT += core gui widgets quickwidgets quick qml serialport concurrent testlib
CONFIG += testcase console c++11
CONFIG -= app_bundle
TEMPLATE = app
TARGET = upgrade_regression
DESTDIR = $$OUT_PWD/run

ROOT = $$clean_path($$PWD/..)
INCLUDEPATH += $$ROOT/Gui_app $$ROOT/Gui_app/FilePath \
    $$ROOT/Gui_app/Page $$ROOT/Gui_app/Page/MenuPage \
    $$ROOT/Gui_app/Page/CtrlPage $$ROOT/Configs $$ROOT/Core $$ROOT/Core/Base \
    $$ROOT/Language $$ROOT/Logger $$ROOT/Preset $$ROOT/Utility \
    $$ROOT/cc $$ROOT/cc/Device

LIBS += -L$$ROOT/bin/Release -lConfigs -lCore -llanguage -llogger \
    -lpreset -lutility -lcc

SOURCES += $$PWD/tst_upgrade_regression.cpp \
    $$files($$ROOT/Gui_app/*.cpp, true)
SOURCES -= $$ROOT/Gui_app/main.cpp $$ROOT/Gui_app/Login/loginDlg.cpp
HEADERS += $$files($$ROOT/Gui_app/*.h, true)
HEADERS -= $$ROOT/Gui_app/Login/loginDlg.h
FORMS += $$ROOT/Gui_app/Page/CtrlPage/upgradepage.ui \
    $$ROOT/Gui_app/Page/CtrlPage/systemsettingpage.ui
RESOURCES += $$ROOT/Gui_app/Resource.qrc $$ROOT/Gui_app/qRc.qrc
