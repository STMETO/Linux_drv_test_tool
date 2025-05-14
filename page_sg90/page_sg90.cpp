#include "page_sg90.h"
#include "ui_page_sg90.h"
#include "sg90_app.h"
#include <QThread>
#include <QDebug>

Page_sg90::Page_sg90(QWidget *parent): QWidget(parent), ui(new Ui::Page_sg90)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->resize(1024, 600);


    ui->sg90_Slider->setRange(0, 180);
    ui->sg90_Slider->setValue(90);
}

Page_sg90::~Page_sg90()
{
    delete ui;
}

QPushButton* Page_sg90::getBackButton() {
    return ui->sg90_Btn_return;  // ⚠️ 确保这是你返回按钮的对象名
}

void Page_sg90::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    if (!sg90_Thread) {
        sg90_worker = new Sg90App();
        sg90_Thread = new QThread(this);
        sg90_worker->moveToThread(sg90_Thread);

        //connect(this, &Page_sg90::angleChanged, sg90_worker, &Sg90App::setAngle,Qt::QueuedConnection);
        connect(this, &Page_sg90::angleChanged, sg90_worker, &Sg90App::setAngle);

        sg90_Thread->start();
    }
}

void Page_sg90::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);

    if (sg90_Thread) {
        sg90_Thread->quit();
        sg90_Thread->wait();

        sg90_worker->deleteLater();     // ✅ 不再直接 delete
        sg90_Thread->deleteLater();     // ✅ 推荐也用 deleteLater

        sg90_Thread = nullptr;
        sg90_worker = nullptr;
    }
}

void Page_sg90::on_sg90_Slider_valueChanged(int value)
{
    ui->sg90_label->setText(QString("角度: %1°").arg(value));  // ✅ 只在这里更新标签
    emit angleChanged(value);                                // ✅ 通知 Sg90App 写设备
}
