#ifndef GAMESTATUSIMAGEPROVIDER_H
#define GAMESTATUSIMAGEPROVIDER_H

#include <QObject>
#include <QQuickImageProvider>

class QImage;
class SettingsProxy;

class GameStatusImageProvider : public QQuickImageProvider
{
protected:
    static SettingsProxy *m_SpSettingsProxy;

public:
    static SettingsProxy *getSpSettingsProxy();
    static void setSpSettingsProxy(SettingsProxy *newSpSettingsProxy);

public:
    GameStatusImageProvider();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif // GAMESTATUSIMAGEPROVIDER_H
