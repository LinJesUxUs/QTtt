#include "gamepainteditem.h"
#include "gamestatusimageprovider.h"
#include <QGuiApplication>
#include <QSettings>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setApplicationName("QTtt");
    app.setOrganizationName("LinJesUxUs");

    QList<QScreen*> scr(app.screens());
    QSize maxSize;
    for ( auto i: std::as_const(scr) ) {
        if (maxSize.isEmpty())
            maxSize = i->size();
        else {
            maxSize.setWidth(qMax(maxSize.width(), i->size().width()));
            maxSize.setHeight(qMax(maxSize.height(), i->size().height()));
        }
    }
    maxSize.setWidth(qMin(maxSize.width(), maxSize.height()));
    maxSize.setHeight(qMin(maxSize.width(), maxSize.height()));
    qDebug() << maxSize;

    QSettings settings;
    settings.beginGroup("GameConfig");
    if (settings.value("fieldQSize").isNull())
    settings.setValue("fieldQSize", QSize(3,3));
    if (settings.value("WinLength").isNull())
        settings.setValue("WinLength", 3);
    if (settings.value("PlayersCount").isNull())
        settings.setValue("PlayersCount", 2);
    if (settings.value("FirstPlayer").isNull())
        settings.setValue("FirstPlayer", 1);
    settings.endGroup();

    QImage imgBuf;
    QList<QString> lst = {"z", "y", "a", "over", "ywin", "awin"};
    settings.beginGroup("images");
    for ( auto i: qAsConst(lst)) {
        if (settings.value(i).isNull()) {
            imgBuf = QImage(QString(":/images/") + i + ".jpg" );
            if (imgBuf.size().width() > maxSize.width())
                imgBuf = imgBuf.scaled(maxSize);
            settings.setValue(i, imgBuf);
        }
    }
    settings.endGroup();

    settings.beginGroup("PlayersConf");
    if (settings.value("1Turn").isNull())
        settings.setValue("1Turn", "y");
    if (settings.value("1Win").isNull())
        settings.setValue("1Win", "ywin");
    if (settings.value("1Name").isNull())
        settings.setValue("1Name", "Player1");
    if (settings.value("2Turn").isNull())
        settings.setValue("2Turn", "a");
    if (settings.value("2Win").isNull())
        settings.setValue("2Win", "awin");
    if (settings.value("2Name").isNull())
        settings.setValue("2Name", "Player2");
    if (settings.value("background").isNull())
        settings.setValue("background", "z");
    if (settings.value("over").isNull())
        settings.setValue("over", "over");
    settings.endGroup();
    settings.sync();

    QQmlApplicationEngine engine;
    qmlRegisterType<GamePaintedItem>( "linjesuxus.game", 1, 0, "Game" );
    engine.addImageProvider( QLatin1String("GameStatus"), new GameStatusImageProvider );
    engine.load(QUrl( "qrc:/src/main.qml" ));

    return app.exec();
}
