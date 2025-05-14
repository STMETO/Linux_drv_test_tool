#ifndef PAGE_HUMI_TEM_H
#define PAGE_HUMI_TEM_H

#include <QWidget>
#include "temp_humi_app.h"
#include <QThread>
#include <QPushButton>
#include "test.h"   //测试页面h
#include "PageManager.h"

namespace Ui {
class Page_humi_tem;
}

class Page_humi_tem : public QWidget
{
    Q_OBJECT

     test *P_test;       //test

public:
    explicit Page_humi_tem(QWidget *parent = nullptr);
    ~Page_humi_tem();

     QPushButton* getBackButton();

protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

private slots:
    void on_Btn_to_test_clicked();

private:
    Ui::Page_humi_tem *ui;
    QThread *dht11_Thread = nullptr;
    TempHumiApp *dht11_worker = nullptr;
    PageManager *pageManager;
};

#endif // PAGE_HUMI_TEM_H
