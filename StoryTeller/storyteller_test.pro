QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#MATERIAL-SDK
LIBS +=$$PWD/libs/libcomponents.a
INCLUDEPATH +=$$PWD/libs/Include


SOURCES += \
    framelessWidget.cpp \
    framelessWidgetDeveloper.cpp \
    framelessWidgetPlayer.cpp \
    main.cpp \
    node.cpp

HEADERS += \
    framelessWidget.h \
    framelessWidgetDeveloper.h \
    framelessWidgetPlayer.h \
    node.h

FORMS += \
    framelessWidget.ui \
    framelessWidgetDeveloper.ui \
    framelessWidgetPlayer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


DISTFILES +=

RESOURCES += \
    res.qrc
