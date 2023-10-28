QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

CONFIG += c++17

VERSION_MAJOR = 0
VERSION_MINOR = 1
VERSION_BUILD = 1
DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
       "VERSION_MINOR=$$VERSION_MINOR"\
       "VERSION_BUILD=$$VERSION_BUILD"

VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}

DEFINES += VERSION_STR=\\\"$${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}\\\"

CONFIG(release debug|release) {
    QMAKE_CXXFLAGS += -Os
    QMAKE_CXXFLAGS += -fstack-protector-all
    DEFINES += QT_NO_DEBUG_OUTPUT
}
else {
    QMAKE_CXXFLAGS += -O0 -g
    DEFINES += DEBUG
}

OUTPUTDIR = build/
DESTDIR = $${OUTPUTDIR}
OBJECTS_DIR = $${OUTPUTDIR} /.obj
MOC_DIR = $${OUTPUTDIR}/.moc
RCC_DIR = $${OUTPUTDIR}/.rcc
UI_DIR = $${OUTPUTDIR}/.ui

SOURCES += \
    samples/Graphics/main.cc \
    sources/Graphics/mainwindow.cc

HEADERS += \
    include/Graphics/mainwindow.hh

FORMS += \
    include/Graphics/mainwindow.ui



#QT       += core gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++17

## You can make your code fail to compile if it uses deprecated APIs.
## In order to do so, uncomment the following line.
##DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#SOURCES += \
#    main.cpp \
#    sources/Graphics/mainwindow.cpp

#HEADERS += \
#    include/Graphics/mainwindow.h

#FORMS += \
#    include/Graphics/mainwindow.ui

## Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
