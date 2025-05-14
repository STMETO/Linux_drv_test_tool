#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class test;
}

class test : public QWidget
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = nullptr);
    ~test();

    QPushButton* getBackButton();


private:
    Ui::test *ui;
};

#endif // TEST_H
