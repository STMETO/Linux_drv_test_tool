#ifndef PAGE_SR04_H
#define PAGE_SR04_H

#include <QWidget>
#include "sr04_app.h"
#include <QThread>
#include <QPushButton>

namespace Ui {
class page_sr04;
}

class page_sr04 : public QWidget
{
    Q_OBJECT

public:
    explicit page_sr04(QWidget *parent = nullptr);
    ~page_sr04();

    QPushButton* getBackButton();

protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

private:
    Ui::page_sr04 *ui;
    QThread *sr04_Thread = nullptr;   //存放sr04线程
    Sr04App *sr04_worker = nullptr;
};

#endif // PAGE_SR04_H
