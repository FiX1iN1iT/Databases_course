QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L"/opt/homebrew/opt/libpq/lib"

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authenticationmanager.cpp \
    databasehelper.cpp \
    formwindow.cpp \
    loginwindow.cpp \
    main.cpp \
    menuwindow.cpp \
    registrationwindow.cpp \
    welcomewindow.cpp

HEADERS += \
    authenticationmanager.h \
    databasehelper.h \
    formwindow.h \
    loginwindow.h \
    menuwindow.h \
    registrationwindow.h \
    welcomewindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
