#ifndef SR04_APP_H
#define SR04_APP_H

#include <QObject>
#include <QTimer>

class Sr04App : public QObject
{
    Q_OBJECT

public:
    explicit Sr04App(QObject *parent = nullptr);
    ~Sr04App();

signals:
    void new_sr04_Data(int len);  // 发给界面的信号

public slots:
    void start_sr04_Work();  // 启动时执行的函数

private:
    QTimer *timer = nullptr;  // 用于定时读取数据

    void readlen();  // 实际距离函数
};

#endif // SR04_APP_H
