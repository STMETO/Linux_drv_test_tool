#ifndef SCREENSLIDE_H
#define SCREENSLIDE_H

//#pragma once
#include <QObject>
#include <QPoint>
#include <QWidget>

class ScreenSlide : public QObject {
    Q_OBJECT
public:
    explicit ScreenSlide(QWidget *target, QObject *parent = nullptr);//第一个参数是要监听的页面

signals:
    void slideLeft();   // 向左滑
    void slideRight();  // 向右滑
    void slideUp();     // 向上滑
    void slideDown();   // 向下滑

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QPoint startPos;         // 滑动起点位置
    QWidget *targetWidget;   // 被监听滑动的对象
};


#endif // SCREENSLIDE_H
