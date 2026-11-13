QT -= gui
QT += serialport xml widgets
LIB_NAME = cc
TEMPLATE = lib
DEFINES += CC_LIBRARY

CONFIG += c++11


CONFIG(debug, debug|release){
    TARGET = $${LIB_NAME}d
    DESTDIR = $$absolute_path($${_PRO_FILE_PWD_}/../bin/Debug/)
    LIBS += -L$$DESTDIR/ -lloggerd \
            -L$$DESTDIR/ -lutilityd \
            -L$$DESTDIR/ -lpresetd \
            -L$$DESTDIR/ -lConfigsd \


}else{
    TARGET = $${LIB_NAME}
    DESTDIR = $$absolute_path($${_PRO_FILE_PWD_}/../bin/Release/)
    LIBS += -L$$DESTDIR/ -llogger \
            -L$$DESTDIR/ -lutility \
            -L$$DESTDIR/ -lpreset \
            -L$$DESTDIR/ -lConfigs \


}

INCLUDEPATH += $$PWD/../Logger \
               $$PWD/../Utility \
               $$PWD/Device \
               $$PWD/../Preset \
               $$PWD/../Configs \


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Device/ComFramedata.cpp \
    Device/crccalculater.cpp \

HEADERS += \
    Device/ComFramedata.h \
    Device/crccalculater.h \
    cc_def.h \
    cc_global.h \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
