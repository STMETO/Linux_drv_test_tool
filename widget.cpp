#include "widget.h"
#include "ui_widget.h"
#include "page_humi_tem.h"
#include "page_sr04.h"
#include "page_sg90.h"
#include "page_album.h"
#include "PageManager.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 创建页面管理器
    pageManager = new PageManager(this);

    // 创建并注册子页面
    P_page_humi_tem = new Page_humi_tem(this);
    P_page_sr04     = new page_sr04(this);
    P_page_sg90     = new Page_sg90(this);
    P_page_Album    = new Page_Album(this);

    // 注册页面，设置入口按钮和返回按钮
    pageManager->registerPage(P_page_humi_tem, this, ui->Btn_humi_temp, P_page_humi_tem->getBackButton());
    pageManager->registerPage(P_page_sr04,     this, ui->Btn_sr04,      P_page_sr04->getBackButton());
    pageManager->registerPage(P_page_sg90,     this, ui->Btn_sg90,      P_page_sg90->getBackButton());
    pageManager->registerPage(P_page_Album,    this, ui->Btn_album,     P_page_Album->getBackButton());
}

Widget::~Widget()
{
    delete ui;
}
