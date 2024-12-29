#include "gamestatusimageprovider.h"
#include "settingsproxy.h"

SettingsProxy *GameStatusImageProvider::m_SpSettingsProxy = nullptr;

SettingsProxy *GameStatusImageProvider::getSpSettingsProxy()
{
    return m_SpSettingsProxy;
}

void GameStatusImageProvider::setSpSettingsProxy(SettingsProxy *newSpSettingsProxy)
{
    m_SpSettingsProxy = newSpSettingsProxy;
}

GameStatusImageProvider::GameStatusImageProvider() : QQuickImageProvider( QQuickImageProvider::Image ) {}

QImage GameStatusImageProvider::requestImage(const QString &id, QSize * /*size*/, const QSize & /*requestedSize*/)
{
    if (m_SpSettingsProxy == nullptr)
        return QImage();
    if (m_SpSettingsProxy->getSpSettings() == nullptr)
        return QImage();

    QStringList lst = id.split(" ");
    QImage img;
    if (lst.first() == "Game" && lst.last() == "Over!" ) {
        img = m_SpSettingsProxy->value("images/" + m_SpSettingsProxy->value("playersConf/over").toString() ).value<QImage>();
        return img;
    }
    for ( uint i = 1; i <= m_SpSettingsProxy->getPlayersCount(); ++i ) {
        if (m_SpSettingsProxy->getPlayersConf(QString::number(i) + "Name") == lst.first() )
            img = m_SpSettingsProxy->value("images/" + m_SpSettingsProxy->getPlayersConf(QString::number(i) + "Turn")).value<QImage>();
    }
    return img;
}
