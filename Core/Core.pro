QT -= gui
QT += serialport

LIB_NAME = Core
TEMPLATE = lib
DEFINES += CORE_LIBRARY

CONFIG += c++11

INCLUDEPATH += $$PWD/../Language \
               $$PWD/../Logger \
               $$PWD/../UserLogin \
               $$PWD/../cc \
               $$PWD/../cc/Device \
               $$PWD/Base \
               $$PWD/../Preset \

CONFIG(debug, debug|release){
    TARGET = $${LIB_NAME}d
    DESTDIR = $$absolute_path($${_PRO_FILE_PWD_}/../bin/Debug/)
    LIBS += -L$$DESTDIR/ -lloggerd \
            -L$$DESTDIR/ -lpresetd \
            -L$$DESTDIR/ -lutilityd \
            -L$$DESTDIR/ -lccd \
            -L$$DESTDIR/ -lpresetd \


}else{
    TARGET = $${LIB_NAME}
    DESTDIR = $$absolute_path($${_PRO_FILE_PWD_}/../bin/Release/)
    LIBS += -L$$DESTDIR/ -llogger \
            -L$$DESTDIR/ -lpreset \
            -L$$DESTDIR/ -lutility \
            -L$$DESTDIR/ -lcc \
            -L$$DESTDIR/ -lpreset \

}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CmdExecutor.cpp \
    command_def.cpp \
    messageprocesser.cpp \
    upgradectrlmgr.cpp

HEADERS += \
    Base/FilePath.h \
    CmdExecutor.h \
    Core_def.h \
    Core_global.h \
    command_def.h \
    messageprocesser.h \
    upgradectrlmgr.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
