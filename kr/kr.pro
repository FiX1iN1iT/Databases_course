QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L"/opt/homebrew/opt/libpq/lib"

CONFIG += c++17

SOURCES += \
    loginwindow.cpp \
    main.cpp \
    registrationwindow.cpp

HEADERS += \
    loginwindow.h \
    registrationwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target