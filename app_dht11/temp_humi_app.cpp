#include "temp_humi_app.h"
#include <QDebug>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int fd;

TempHumiApp::TempHumiApp(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TempHumiApp::readTempHumi);
}

TempHumiApp::~TempHumiApp()
{
    timer->stop();
    if (fd > 0){
        close(fd);
    }
}


void dht11_init(void)
{
    fd = open("/dev/fxy_dht11", O_RDWR | O_NONBLOCK);
    if (fd < 0)
    {
        qDebug()<<"open /dev/mydht11 failed";
    }
}
int dht11_read(char *humi, char *temp)
{
    char buf[2];
    if (2 == read(fd, buf, 2))
    {
        *humi = buf[0];
        *temp = buf[1];
        return 0;
    }
    else
    {
        return -1;
    }
}

void TempHumiApp::start_dht11_Work()
{
    dht11_init();
    timer->start(2000);  // 每2秒读取一次
}

void TempHumiApp::readTempHumi()
{
    char temp = 0;
    char humi = 0;
    if (dht11_read(&humi, &temp) == 0)
    {
        qDebug() << QString("温度: %1°C  湿度: %2%").arg((int)temp).arg((int)humi);
        emit new_dht11_Data(temp, humi);
    }
    else
    {
        qDebug() << "读取失败";
    }
}
