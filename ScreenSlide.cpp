#include "ScreenSlide.h"
#include <QMouseEvent>
#include <QTouchEvent>
#include <QDebug>

// 构造函数：初始化滑动监听器
ScreenSlide::ScreenSlide(QWidget *target, QObject *parent): QObject(parent), targetWidget(target) {

    // 启用目标控件的触摸事件支持（默认是关闭的）
    targetWidget->setAttribute(Qt::WA_AcceptTouchEvents);

    // 安装事件过滤器，本对象将优先处理 targetWidget 的事件
    targetWidget->installEventFilter(this);
}

// 事件过滤器函数：用于处理鼠标和触摸滑动事件
bool ScreenSlide::eventFilter(QObject *watched, QEvent *event) {
    // 只处理指定目标控件的事件，忽略其他控件传入的事件
    if (watched != targetWidget)
        return QObject::eventFilter(watched, event);  // 默认行为（不拦截）

    const int threshold = 50;  // 判定为“滑动”的最小距离（单位：像素）
    // 捕获鼠标按下事件
    if (event->type() == QEvent::MouseButtonPress) {
        // 将通用 QEvent 类型强转为 QMouseEvent，以访问鼠标坐标
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        startPos = e->pos();  // 记录鼠标按下时的位置
    }

    // 捕获鼠标释放事件，判断是否形成滑动手势
    else if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        QPoint endPos = e->pos();  // 获取松开时的位置

        // 计算水平和垂直方向的位移差
        int deltaX = endPos.x() - startPos.x();
        int deltaY = endPos.y() - startPos.y();

        // 判断为左右滑动（横向优先）
        if (std::abs(deltaX) > std::abs(deltaY) && std::abs(deltaX) > threshold) {
            deltaX < 0 ? emit slideLeft() : emit slideRight();
        }
        // 判断为上下滑动
        else if (std::abs(deltaY) > threshold) {
            deltaY < 0 ? emit slideUp() : emit slideDown();
        }
    }

    // 触摸开始事件：记录起点
    else if (event->type() == QEvent::TouchBegin) {
        QTouchEvent *e = static_cast<QTouchEvent*>(event);
        if (!e->touchPoints().isEmpty()) {
            // 获取第一个触点的坐标（支持多指触控时也只取第一个手指）
            startPos = e->touchPoints().first().pos().toPoint();
        }
    }

    // 触摸结束事件：判断是否滑动
    else if (event->type() == QEvent::TouchEnd) {
        QTouchEvent *e = static_cast<QTouchEvent*>(event);
        if (!e->touchPoints().isEmpty()) {
            QPoint endPos = e->touchPoints().first().pos().toPoint();

            int deltaX = endPos.x() - startPos.x();
            int deltaY = endPos.y() - startPos.y();

            // 横向滑动识别（距离优先）
            if (std::abs(deltaX) > std::abs(deltaY) && std::abs(deltaX) > threshold) {
                deltaX < 0 ? emit slideLeft() : emit slideRight();
            }
            // 纵向滑动识别
            else if (std::abs(deltaY) > threshold) {
                deltaY < 0 ? emit slideUp() : emit slideDown();
            }
        }
    }
    // 所有事件处理完后，继续让 Qt 正常分发事件，不打断
    return QObject::eventFilter(watched, event);
}
