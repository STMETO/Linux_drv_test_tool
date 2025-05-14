#ifndef PAGE_SG90_H
#define PAGE_SG90_H

#include <QWidget>
#include "sg90_app.h"
#include <QThread>
#include <QPushButton>

namespace Ui {
class Page_sg90;
}

class Page_sg90 : public QWidget
{
    Q_OBJECT

public:
    explicit Page_sg90(QWidget *parent = nullptr);
    ~Page_sg90();

    QPushButton* getBackButton();

protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

signals:
    void angleChanged(int angle);  // 仅发送给 Sg90App 用于写设备

private slots:
    void on_sg90_Slider_valueChanged(int value);

private:
    Ui::Page_sg90 *ui;
    QThread *sg90_Thread = nullptr;   //存放sg90线程
    Sg90App *sg90_worker = nullptr;
};

#endif // PAGE_SG90_H
