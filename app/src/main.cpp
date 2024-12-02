#include "gamepainteditem.h"
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlFileSelector>
#include <QQuickView>
#include <QDir>
#include <QSettings>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setApplicationName("LinJesUxUs");
    app.setOrganizationName("QTtt");

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

    settings.beginGroup("images");
    if (settings.value("z").isNull())
        settings.setValue("z", QImage(":/images/z.jpg"));
    if (settings.value("y").isNull())
        settings.setValue("y", QImage(":/images/y.jpg"));
    if (settings.value("a").isNull())
        settings.setValue("a", QImage(":/images/a.jpg"));
    if (settings.value("over").isNull())
        settings.setValue("over", QImage(":/images/over.jpg"));
    if (settings.value("ywin").isNull())
        settings.setValue("ywin", QImage(":/images/ywin.jpg"));
    if (settings.value("awin").isNull())
        settings.setValue("awin", QImage(":/images/awin.jpg"));
    settings.endGroup();
    settings.sync();

    QQuickView view;
    qmlRegisterType<GamePaintedItem>( "linjesuxus.game", 1, 0, "Game" );
    view.connect( view.engine(), SIGNAL(quit()), &app, SLOT(quit()) );
    view.setSource( QUrl( "qrc:/src/main.qml" ) );
    view.setResizeMode( QQuickView::SizeRootObjectToView );
    view.show();
    return app.exec();
}
