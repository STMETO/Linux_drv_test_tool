#include "page_sr04.h"
#include "ui_page_sr04.h"
#include "widget.h"
#include "sr04_app.h"
#include <QDebug>

page_sr04::page_sr04(QWidget *parent) :QWidget(parent),ui(new Ui::page_sr04)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window);     //成为顶层窗口
    this->resize(1024, 600);                //给它合适的窗口大小

}

page_sr04::~page_sr04()
{
    delete ui;
}

QPushButton* page_sr04::getBackButton() {
    return ui->Btn_return;  // ⚠️ 确保这是你返回按钮的对象名
}

void page_sr04::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);// 保留父类行为

    if (!sr04_Thread) {
        sr04_Thread = new QThread(this);
        sr04_worker = new Sr04App();

        sr04_worker->moveToThread(sr04_Thread);

        connect(sr04_Thread, &QThread::started, sr04_worker, &Sr04App::start_sr04_Work);
        connect(sr04_worker, &Sr04App::new_sr04_Data, this, [=](int len){
            ui->label_sr04_len->setText(QString("超声波距离: %1 cm").arg(len));
        });

        sr04_Thread->start();
    }
}

void page_sr04::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);// 保留父类行为

    qDebug() << "超声波页面页面退出\n";
    if (sr04_Thread) {
        sr04_Thread->quit();
        sr04_Thread->wait();

        sr04_worker->deleteLater();     // ✅ 不再直接 delete
        sr04_Thread->deleteLater();     // ✅ 推荐也用 deleteLater

        sr04_worker = nullptr;
        sr04_Thread = nullptr;
    }
}
