#ifndef TEMP_HUMI_APP_H
#define TEMP_HUMI_APP_H

#include <QObject>
#include <QTimer>

class TempHumiApp : public QObject
{
    Q_OBJECT

public:
    explicit TempHumiApp(QObject *parent = nullptr);
    ~TempHumiApp();

signals:
    void new_dht11_Data(int temperature, int humidity);  // 发给界面的信号

public slots:
    void start_dht11_Work();  // 启动时执行的函数

private:
    QTimer *timer = nullptr;  // 用于定时读取数据

    void readTempHumi();  // 实际读取温湿度数据的函数
};


#endif // TEMP_HUMI_APP_H

