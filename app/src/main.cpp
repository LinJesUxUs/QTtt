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

    QSettings settings;
    settings.beginGroup("gameConfig");
    if (settings.value("fieldWidth").isNull())
        settings.setValue("fieldWidth", 3);
    if (settings.value("fieldHeight").isNull())
        settings.setValue("fieldHeight", 3);
    if (settings.value("winLength").isNull())
        settings.setValue("winLength", 3);
    if (settings.value("playersCount").isNull())
        settings.setValue("playersCount", 2);
    if (settings.value("firstPlayer").isNull())
        settings.setValue("firstPlayer", 1);
    settings.endGroup();

    QImage imgBuf;
    QList<QString> lst = {"Alice",
                          "AliceWin",
                          "Bob",
                          "BobWin",
                          "Chuck",
                          "BackGround"};
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

    settings.beginGroup("playersConf");
    if (settings.value("1Turn").isNull())
        settings.setValue("1Turn", "Alice");
    if (settings.value("1Win").isNull())
        settings.setValue("1Win", "AliceWin");
    if (settings.value("1Name").isNull())
        settings.setValue("1Name", "Alice");
    if (settings.value("2Turn").isNull())
        settings.setValue("2Turn", "Bob");
    if (settings.value("2Win").isNull())
        settings.setValue("2Win", "BobWin");
    if (settings.value("2Name").isNull())
        settings.setValue("2Name", "Bob");
    if (settings.value("background").isNull())
        settings.setValue("background", "BackGround");
    if (settings.value("over").isNull())
        settings.setValue("over", "Chuck");
    settings.endGroup();
    settings.sync();

    QQmlApplicationEngine engine;
    qmlRegisterType<GamePaintedItem>( "linjesuxus.game", 1, 0, "Game" );
    engine.addImageProvider( QLatin1String("GameStatus"), new GameStatusImageProvider );
    engine.load(QUrl( "qrc:/src/ViewsComposer.qml" ));

    return app.exec();
}
