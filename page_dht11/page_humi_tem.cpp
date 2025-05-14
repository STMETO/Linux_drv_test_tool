#include "page_humi_tem.h"
#include "ui_page_humi_tem.h"
#include "widget.h"
#include "temp_humi_app.h"
#include <QDebug>
#include "PageManager.h"

#include "test.h"   //测试页面h

Page_humi_tem::Page_humi_tem(QWidget *parent) :QWidget(parent),ui(new Ui::Page_humi_tem)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window);     //成为顶层窗口
    this->resize(1024, 600);                 //给它合适的窗口大小

    // 创建页面管理器
    pageManager = new PageManager(this);

    P_test = new test(this);

    // 注册页面，设置入口按钮和返回按钮
    pageManager->registerPage(P_test, this, ui->Btn_to_test, P_test->getBackButton());

}

Page_humi_tem::~Page_humi_tem()
{
    delete ui;
}

QPushButton* Page_humi_tem::getBackButton() {
    return ui->Btn_return;  // ⚠️ 确保这是你返回按钮的对象名
}

void Page_humi_tem::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);  // 保留父类行为

    if (!dht11_Thread) {
        dht11_Thread = new QThread(this);
        dht11_worker = new TempHumiApp();

        dht11_worker->moveToThread(dht11_Thread);

        connect(dht11_Thread, &QThread::started, dht11_worker, &TempHumiApp::start_dht11_Work);
        connect(dht11_worker, &TempHumiApp::new_dht11_Data, this, [=](int temp, int humi){
            ui->temp->setText(QString("温度: %1 °C").arg(temp));
            ui->humi->setText(QString("湿度: %1 %").arg(humi));
        });

        dht11_Thread->start();
    }
}

void Page_humi_tem::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);  // 保留父类行为

    qDebug() << "温湿度页面退出\n";
    if (dht11_Thread) {
        dht11_Thread->quit();
        dht11_Thread->wait();

        dht11_worker->deleteLater();     // ✅ 不再直接 delete
        dht11_Thread->deleteLater();     // ✅ 推荐也用 deleteLater

        dht11_worker = nullptr;
        dht11_Thread = nullptr;
    }
}

