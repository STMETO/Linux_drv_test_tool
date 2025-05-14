#include "page_album.h"
#include "ui_page_album.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>

Page_Album::Page_Album(QWidget *parent) :QWidget(parent),ui(new Ui::Page_Album)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window);     //成为顶层窗口
    this->resize(1024, 600);                 //给它合适的窗口大小

    slideDetector = new ScreenSlide(this,this);

    connect(slideDetector, &ScreenSlide::slideLeft, this, [=]() {
        //if (albumWorker)：确认对象已存在（不为空）；
        //QMetaObject::invokeMethod(...)：使用 元对象系统 反射式调用 albumWorker 中名为 "next" 的槽函数。
        //为什么不用 albumWorker->next() 而用 QMetaObject::invokeMethod(...)？
        //为什么不用 albumWorker->next() 而用 QMetaObject::invokeMethod(...)？
        if (albumWorker) QMetaObject::invokeMethod(albumWorker, "next", Qt::QueuedConnection);
    });
    connect(slideDetector, &ScreenSlide::slideRight, this, [=]() {
        //QMetaObject::invokeMethod(..., Qt::QueuedConnection) 的作用：
        //自动跨线程调用：它会将调用请求排入子线程事件队列，由子线程自己去调用 next()；
        if (albumWorker) QMetaObject::invokeMethod(albumWorker, "prev", Qt::QueuedConnection);
    });

}

Page_Album::~Page_Album()
{
    delete ui;
}


QPushButton* Page_Album::getBackButton() {
    return ui->Album_Btn_return;  // ⚠️ 确保这是你返回按钮的对象名
}

void Page_Album::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    if (!albumThread) {
        albumWorker = new AlbumApp();
        albumThread = new QThread(this);
        albumWorker->moveToThread(albumThread);

        // ✅ 默认使用资源文件方式加载
        QStringList imgs = {
            ":/Album_res/images/image1.jpeg",
            ":/Album_res/images/image2.jpeg",
            ":/Album_res/images/image3.jpeg"
        };
        // ❗如需使用项目路径下图片，请取消下面注释：
        /*
        QString basePath = QCoreApplication::applicationDirPath();
        QStringList imgs = {
            basePath + "/images/1.jpg",
            basePath + "/images/2.jpg",
            basePath + "/images/3.jpg"
        };
        */

        albumWorker->setImageList(imgs);

        connect(ui->btn_next, &QPushButton::clicked, albumWorker, &AlbumApp::next);
        connect(ui->btn_prev, &QPushButton::clicked, albumWorker, &AlbumApp::prev);
        connect(ui->auto_play, &QRadioButton::toggled, albumWorker, &AlbumApp::toggleAutoPlay);

        connect(albumThread, &QThread::started, albumWorker, &AlbumApp::start);
        connect(albumWorker, &AlbumApp::newImage, this, [=](const QString &path, int index, int total) {
            QPixmap pix(path);      //创建图片对象
            if (pix.isNull()) {     //判断图片是否加载失败
                qWarning() << "无法加载图片：" << path;
                return;
            }
            //把图片按照比例缩放到 imageLabel 的大小并显示出来：
            ui->imageLabel->setPixmap(pix.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio));
            ui->label_img_Name->setText(QFileInfo(path).fileName());
            ui->label_img_Num->setText(QString("%1 / %2").arg(index).arg(total));
        });

        albumThread->start();
    }
}

void Page_Album::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);

    if (albumWorker && albumThread) {
        QMetaObject::invokeMethod(albumWorker, "stop", Qt::QueuedConnection);
        albumThread->quit();
        albumThread->wait();

        albumWorker->deleteLater();
        albumThread->deleteLater();

        albumWorker = nullptr;
        albumThread = nullptr;
    }
}
