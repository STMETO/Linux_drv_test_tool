#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QMap>

class PageManager : public QObject {
    Q_OBJECT
public:
    explicit PageManager(QObject *parent = nullptr);

    // 注册页面，设置显示按钮和返回按钮（可选）
    void registerPage(QWidget *page, QWidget *backToPage, QPushButton *entryButton, QPushButton *backButton = nullptr);

private:
    void styleAsIconButton(QPushButton *button); // 设置图标按钮样式

private:
    QVector<QWidget*> pages;
    QMap<QWidget*, QWidget*> backPageMap;  // 每个页面对应的返回页
};

#endif // PAGEMANAGER_H
