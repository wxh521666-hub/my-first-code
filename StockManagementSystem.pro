QT       += core gui
#自己添加的
QT += sql
#sss
QT += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcommodity.cpp \
    delivehouse.cpp \
    goodswarehouse.cpp \
    main.cpp \
    mainwidget.cpp

HEADERS += \
    addcommodity.h \
    delivehouse.h \
    goodswarehouse.h \
    mainwidget.h

FORMS += \
    addcommodity.ui \
    delivehouse.ui \
    goodswarehouse.ui \
    mainwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../back.qrc \
    ../icons/incon1.qrc \
    ../icons2.qrc
