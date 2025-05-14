#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}

//export QT_QPA_GENERIC_PLUGINS=tslib:/dev/input/event1
//export QT_QPA_PLATFORM=linuxfb:fb=/dev/fb0
//export QT_QPA_FONTDIR=/usr/lib/fonts/
