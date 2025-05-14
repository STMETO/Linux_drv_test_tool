QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    PageManager.cpp \
    ScreenSlide.cpp \
    app_album/Album_app.cpp \
    app_dht11/temp_humi_app.cpp \
    app_sg90/sg90_app.cpp \
    app_sr04/sr04_app.cpp \
    main.cpp \
    page_album/page_album.cpp \
    page_dht11/page_humi_tem.cpp \
    page_dht11/test.cpp \
    page_sg90/page_sg90.cpp \
    page_sr04/page_sr04.cpp \
    widget.cpp

HEADERS += \
    PageManager.h \
    ScreenSlide.h \
    app_album/Album_app.h \
    app_dht11/temp_humi_app.h \
    app_sg90/sg90_app.h \
    app_sr04/sr04_app.h \
    page_album/page_album.h \
    page_dht11/page_humi_tem.h \
    page_dht11/test.h \
    page_sg90/page_sg90.h \
    page_sr04/page_sr04.h \
    widget.h

FORMS += \
    ui_album/page_album.ui \
    ui_dht11/page_humi_tem.ui \
    ui_dht11/test.ui \
    ui_sg90/page_sg90.ui \
    ui_sr04/page_sr04.ui \
    widget.ui

INCLUDEPATH += $$PWD/app_album \
               $$PWD/app_dht11 \
               $$PWD/app_sg90 \
               $$PWD/app_sr04 \
               $$PWD/page_album \
               $$PWD/page_dht11 \
               $$PWD/page_sr04 \
               $$PWD/page_sg90

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Icon/album.png \
    Icon/dht11.png \
    Icon/sg90.png \
    Icon/sr04.png \
    images/image1.jpeg \
    images/image2.jpeg \
    images/image3.jpeg \
    images/image4.jpeg

RESOURCES += \
    Album_images.qrc \
    Background_img.qrc \
    Btn_Icon.qrc



