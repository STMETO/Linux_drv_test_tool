#ifndef SG90_APP_H
#define SG90_APP_H

#include <QObject>

class Sg90App : public QObject {
    Q_OBJECT  // 必须加这个宏才能使用 signals/slots

public:
    explicit Sg90App(QObject *parent = nullptr);

public slots:
    void setAngle(int angle);  // 控制舵机角度
};

#endif
