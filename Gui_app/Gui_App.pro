QT       += core gui serialport widgets quickwidgets quick qml concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
TARGET = TrendWinUpgradeTool
TEMPLATE = app
RC_ICONS = logo.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_QML_DEBUG_NO_WARNING

INCLUDEPATH += $$PWD/../Language \
               $$PWD/../Logger \
               $$PWD/../Core \
               $$PWD/../Core/Base \
               $$PWD/FilePath \
               $$PWD/../Preset \
               $$PWD/../Utility \
               $$PWD/../cc \
               $$PWD/../cc/Device \
               $$PWD/../Configs \
               $$PWD/Page \
               $$PWD/Page/MenuPage \
               $$PWD/Page/CtrlPage \
               $$PWD/Page/MainPage \
               $$PWD/Page/CmdPage




CONFIG(debug, debug|release){
    DESTDIR = $$absolute_path($${_PRO_FILE_PWD_}/../bin/Debug/)
    LIBS += -L$$DESTDIR/ -llanguaged \
            -L$$DESTDIR/ -lloggerd \
            -L$$DESTDIR/ -lCored \
            -L$$DESTDIR/ -lpresetd \
            -L$$DESTDIR/ -lutilityd \
            -L$$DESTDIR/ -lccd \
            -L$$DESTDIR/ -lConfigsd \
            -L$$DESTDIR/ -utilityd \


}else{
    DESTDIR = $$absolute_path($${_PRO_FILE_PWD_}/../bin/Release/)
    LIBS += -L$$DESTDIR/ -llanguage \
            -L$$DESTDIR/ -llogger \
            -L$$DESTDIR/ -lCore \
            -L$$DESTDIR/ -lpreset \
            -L$$DESTDIR/ -lutility \
            -L$$DESTDIR/ -lcc \
            -L$$DESTDIR/ -lConfigs \
            -L$$DESTDIR/ -utility \

}



SOURCES += \
    AnalyzerWinFrame.cpp \
    FilePath/filepathmgr.cpp \
    Page/CtrlPage/aboutPage.cpp \
    Page/CtrlPage/systemsettingpage.cpp \
    Page/CtrlPage/upgradepage.cpp \
    Page/MenuPage/ctrlmenuWidget.cpp \
    Page/mainframe.cpp \
    Page/statusbarwidget.cpp \
    Page/workpageframe.cpp \
    main.cpp \
    systemroot.cpp \
    sysversion.cpp \
    uistylemanager.cpp

HEADERS += \
    AnalyzerWinFrame.h \
    FilePath/filepathmgr.h \
    Gui_def.h \
    Page/CtrlPage/aboutPage.h \
    Page/CtrlPage/systemsettingpage.h \
    Page/CtrlPage/upgradepage.h \
    Page/MenuPage/ctrlmenuWidget.h \
    Page/mainframe.h \
    Page/statusbarwidget.h \
    Page/workpageframe.h \
    systemroot.h \
    sysversion.h \
    uistylemanager.h

FORMS += \
    AnalyzerWinFrame.ui \
    Page/CtrlPage/systemsettingpage.ui \
    Page/CtrlPage/upgradepage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    Login/qml/Login.qml

RESOURCES += \
    Resource.qrc \
    qRc.qrc

DISTFILES += \
    Page/CtrlPage/qml/UpgradePage.qml


