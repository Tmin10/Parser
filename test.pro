QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = parser-gui
TEMPLATE = app


SOURCES += main.cpp \
    http.cpp \
    mainwindow.cpp

HEADERS  += \
    http.h \
    mainwindow.h



#TEMPLATE = app
#CONFIG += console
#CONFIG -= qt

#SOURCES += main.cpp \
#    http.cpp

#HEADERS += \
#    http.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    res.qrc

