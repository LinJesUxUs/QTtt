#ifndef GAMESTATUSIMAGEPROVIDER_H
#define GAMESTATUSIMAGEPROVIDER_H

#include <QObject>
#include <QQuickImageProvider>

class QImage;
class QSettings;

class GameStatusImageProvider : public QQuickImageProvider
{
protected:
    QSettings *settings = nullptr;

public:
    GameStatusImageProvider();
    ~GameStatusImageProvider();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif // GAMESTATUSIMAGEPROVIDER_H
