QT       += core gui widgets quickwidgets quick qml

LIB_NAME = userLogin
TEMPLATE = lib
DEFINES += USERLOGIN_LIBRARY

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
    user.cpp \
    userlogin.cpp

HEADERS += \
    UserLogin_global.h \
    user.h \
    user_define.h \
    userlogin.h \
    userlogin_module_name_def.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
