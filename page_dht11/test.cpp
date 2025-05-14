#include "test.h"
#include "ui_test.h"

test::test(QWidget *parent) :QWidget(parent),ui(new Ui::test)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window);     //成为顶层窗口
    this->resize(1024, 600);                 //给它合适的窗口大小
}

test::~test()
{
    delete ui;
}

QPushButton* test::getBackButton() {
    return ui->Btn_test_return;  // ⚠️ 确保这是你返回按钮的对象名
}
