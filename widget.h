#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "PageManager.h"
#include "page_humi_tem.h"  //温湿度的头文件
#include "page_sr04.h"      //sr04的头文件
#include "page_sg90.h"      //sg90的头文件
#include "page_album.h"     //相册的头文件

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    Page_humi_tem *P_page_humi_tem; //保存温湿度页面的实例化地址
    page_sr04 *P_page_sr04;         //保存sr04页面的实例化地址
    Page_sg90 *P_page_sg90;         //保存sg90页面的实例化地址
    Page_Album *P_page_Album;       //保存sg90页面的实例化地址

private slots:
    void on_Btn_humi_temp_clicked();
    void on_Btn_sr04_clicked();
    void on_Btn_sg90_clicked();
    void on_Btn_album_clicked();

private:
    Ui::Widget *ui;
    PageManager *pageManager;
};
#endif // WIDGET_H
