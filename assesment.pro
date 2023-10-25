QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clickablelabel.cpp \
    listwidget.cpp \
    loggerservice.cpp \
    main.cpp \
    mainwindow.cpp \
    rssfeeddata.cpp \
    rssitemdelegate.cpp \
    rssitemui.cpp \
    rssxmlreader.cpp

HEADERS += \
    clickablelabel.h \
    listwidget.h \
    loggerservice.h \
    mainwindow.h \
    rssfeeddata.h \
    rssitemdelegate.h \
    rssitemui.h \
    rssxmlreader.h

FORMS += \
    mainwindow.ui \
    rssitemui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
