#include "Album_app.h"
#include <QDebug>

AlbumApp::AlbumApp(QObject *parent) : QObject(parent), currentIndex(0) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AlbumApp::next);
}

void AlbumApp::setImageList(const QStringList &list) {
    imageList = list;
}

void AlbumApp::start() {
    if (!imageList.isEmpty()) {
        emit newImage(imageList[currentIndex], currentIndex + 1, imageList.size());
    }
}

void AlbumApp::stop() {
    timer->stop();
}

void AlbumApp::next() {
    if (imageList.isEmpty()) return;
    currentIndex = (currentIndex + 1) % imageList.size();
    emit newImage(imageList[currentIndex], currentIndex + 1, imageList.size());
}

void AlbumApp::prev() {
    if (imageList.isEmpty()) return;
    currentIndex = (currentIndex - 1 + imageList.size()) % imageList.size();
    emit newImage(imageList[currentIndex], currentIndex + 1, imageList.size());
}

void AlbumApp::toggleAutoPlay(bool on) {
    if (on)
        timer->start(1500); // 每2秒切换
    else
        timer->stop();
}
