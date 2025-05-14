#ifndef PAGE_ALBUM_H
#define PAGE_ALBUM_H

#include <QWidget>
#include "Album_app.h"
#include <QThread>
#include <QPushButton>
#include "ScreenSlide.h"

namespace Ui {
class Page_Album;
}

class Page_Album : public QWidget
{
    Q_OBJECT

public:
    explicit Page_Album(QWidget *parent = nullptr);
    ~Page_Album();

    QPushButton* getBackButton();   //用于将返回按钮返回到pagemanager

protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

private:
    Ui::Page_Album *ui;
    AlbumApp *albumWorker = nullptr;
    QThread *albumThread = nullptr;
    ScreenSlide *slideDetector = nullptr;   //屏幕滑动

};

#endif // PAGE_ALBUM_H
