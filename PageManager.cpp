#include "PageManager.h"
#include <QPushButton>
#include <QDebug>

PageManager::PageManager(QObject *parent) : QObject(parent) {}

// 哪个页面发出的，返回哪个页面，当前页面的进入按钮 ，返回按钮
void PageManager::registerPage(QWidget *page, QWidget *backToPage, QPushButton *entryButton, QPushButton *backButton)
{
    pages.append(page);             // 把页面加入统一管理列表中
    backPageMap[page] = backToPage; //记录每一个页面与它要返回页面的映射

    // 设置进入按钮行为
    if (entryButton) {
        styleAsIconButton(entryButton);
        connect(entryButton, &QPushButton::clicked, [=]() {
            for (auto *p : pages)
                p->hide();    // 隐藏所有页面
            page->show();     // 显示当前目标页面
        });
    }

    // 设置返回按钮行为
    if (backButton) {
        connect(backButton, &QPushButton::clicked, [=]() {
            QWidget *backTarget = backPageMap.value(page, nullptr);
            if (backTarget) {
                page->hide();
                backTarget->show();
            }
        });
    }

    page->hide();
}

void PageManager::styleAsIconButton(QPushButton *button)
{
    button->setMinimumSize(80, 80);
    button->setIconSize(QSize(64, 64));
    button->setFlat(false);
    button->setStyleSheet(R"(
                          QPushButton {
                          border: 2px solid #8f8f91;
                          border-radius: 10px;
                          background-color: #f0f0f0;
                          padding: 5px;
                          }
                          QPushButton:hover {
                          background-color: #d0d0d0;
                          border: 2px solid #5a5a5a;
                          }
                          QPushButton:pressed {
                          background-color: #c0c0c0;
                          }
                          )");
}
