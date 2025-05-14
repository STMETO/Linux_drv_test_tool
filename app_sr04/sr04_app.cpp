#include "sr04_app.h"
#include <QDebug>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <sys/ioctl.h>

#define CMD_TRIG  100
static int fd;
struct pollfd fds[1];	//使用poll机制

Sr04App::Sr04App(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Sr04App::readlen);
}

Sr04App::~Sr04App()
{
    timer->stop();
    if (fd > 0){
        close(fd);
    }
}

void sr04_init()
{
    fd = open("/dev/fxy_sr04", O_RDWR | O_NONBLOCK);  // 推荐非阻塞模式
    if (fd < 0) {
        qDebug() << "open /dev/fxy_sr04 failed";
    } else {
        qDebug() << "open /dev/fxy_sr04 success";
    }
}

int sr04_read(int *len)
{
    if (fd < 0)
        return -1;

    ioctl(fd, CMD_TRIG);  // 触发测距

    //struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLIN;

    int ret = poll(fds, 1, 1000);  // 最多等 1s
    if (ret == 1 && (fds[0].revents & POLLIN)) {
        int val;
        if (read(fd, &val, 4) == 4) {
            *len = val * 17 / 1000000;
            return 0;
        }
    }
    return -1;
}

void Sr04App::start_sr04_Work()
{
    sr04_init();
    timer->start(500);  // 每0.5秒读取一次
}

void Sr04App::readlen()
{
    int len_cm = 0;
    if (sr04_read(&len_cm) == 0) {
        qDebug() << "测得距离:" << len_cm << "cm";
        emit new_sr04_Data(len_cm);
    } else {
        qDebug() << "测距失败或超时";
    }
}
