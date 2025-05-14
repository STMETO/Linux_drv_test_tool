#ifndef ALBUM_APP_H
#define ALBUM_APP_H


#include <QObject>
#include <QStringList>
#include <QTimer>

class AlbumApp : public QObject
{
    Q_OBJECT
public:
    explicit AlbumApp(QObject *parent = nullptr);
    void setImageList(const QStringList &list);
public slots:
    void start();
    void stop();
    void next();
    void prev();
    void toggleAutoPlay(bool on);

signals:
    void newImage(const QString &path, int index, int total);

private:
    QStringList imageList;
    int currentIndex;
    QTimer *timer = nullptr;
};


#endif // ALBUM_APP_H
