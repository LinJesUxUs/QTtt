#include "gamestatusimageprovider.h"
#include <QSettings>
#include <QtCore>

GameStatusImageProvider::GameStatusImageProvider() : QQuickImageProvider( QQuickImageProvider::Image ) {
    QCoreApplication::setApplicationName("LinJesUxUs");
    QCoreApplication::setOrganizationName("QTtt");
    if (settings == nullptr)
        settings = new QSettings();
}

GameStatusImageProvider::~GameStatusImageProvider()
{
    if (settings != nullptr)
        delete settings;
}

QImage GameStatusImageProvider::requestImage(const QString &id, QSize * /*size*/, const QSize & /*requestedSize*/)
{
    // settings->sync();
    QStringList lst = id.split(" ");
    QImage img;
    if (lst.first() == "Game" ) {
        img = settings->value("images/" + settings->value("PlayersConf/over").toString() ).value<QImage>();
        return img;
    }
    for ( uint i = 1; i <= settings->value("GameConfig/PlayersCount").toUInt(); ++i ) {
        if (settings->value("PlayersConf/" + QString::number(i) + "Name").toString() == lst.first() )
            img = settings->value("images/" + settings->value("PlayersConf/" + QString::number(i) + "Turn").toString() ).value<QImage>();
    }
    return img;
}
