#-------------------------------------------------
#
# Project created by QtCreator 2018-08-27T21:34:08
#
#-------------------------------------------------

QT       += core gui widgets network multimedia

TARGET = HotFight
TEMPLATE = app
RC_FILE = logo.rc
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    playeritem.cpp \
    player1p.cpp \
    player2p.cpp \
    startwindow.cpp \
    netconnectdialog.cpp \
    localgamewindow.cpp \
    gamescene.cpp \
    localgamescene.cpp \
    netgamescene.cpp \
    netgamewindow.cpp \
    keyboardbuffer.cpp \
    rule.cpp \
    helthybar.cpp \
    energybar.cpp \
    explodingitem.cpp \
    endwindow.cpp \
    net.cpp \
    netplayer1p.cpp \
    netplayer2p.cpp \
    guiflyitem.cpp \
    angerbar.cpp \
    help.cpp

HEADERS += \
    playeritem.h \
    player1p.h \
    player2p.h \
    startwindow.h \
    netconnectdialog.h \
    localgamewindow.h \
    gamescene.h \
    localgamescene.h \
    netgamescene.h \
    netgamewindow.h \
    keyboardbuffer.h \
    rule.h \
    healthybar.h \
    energybar.h \
    explodingitem.h \
    endwindow.h \
    net.h \
    netplayer1p.h \
    netplayer2p.h \
    guiflyitem.h \
    angerbar.h \
    help.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

FORMS += \
    startwindow.ui \
    netconnectdialog.ui \
    endwindow.ui \
    help.ui
