QT -= gui

LIB_NAME = preset
TEMPLATE = lib
DEFINES += PRESET_LIBRARY

CONFIG += c++11


CONFIG(debug, debug|release){
    TARGET = $${LIB_NAME}d
    DESTDIR = $$absolute_path($${_PRO_FILE_PWD_}/../bin/Debug/)
}else{
    TARGET = $${LIB_NAME}
    DESTDIR = $$absolute_path($${_PRO_FILE_PWD_}/../bin/Release/)
}
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    presetObj.cpp \
    presetSvrMgr.cpp \
    presetsvr.cpp \
    systempreset.cpp

HEADERS += \
    PresetItemDef.h \
    Preset_global.h \
    presetObj.h \
    presetSvrMgr.h \
    presetsvr.h \
    systempreset.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
