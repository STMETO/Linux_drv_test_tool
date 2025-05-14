#include "sg90_app.h"
#include <QDebug>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>

Sg90App::Sg90App(QObject *parent) : QObject(parent) {}

void Sg90App::setAngle(int angle)
{
    qDebug() << "[Sg90App] 设置角度：" << angle;

    int fd = open("/dev/fxy_sg90", O_WRONLY);
    if (fd < 0) {
        qWarning() << "无法打开设备 /dev/fxy_sg90:" << strerror(errno);
        return;
    }

    // 将 angle 转成 1 字节数据
    uint8_t val = static_cast<uint8_t>(angle);

    int ret = write(fd, &val, 1);
    if (ret < 0) {
        qWarning() << "写入失败：" << strerror(errno);
    }

    close(fd);
}

