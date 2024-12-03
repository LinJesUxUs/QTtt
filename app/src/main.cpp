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
    settings.sync();

    QQuickView view;
    qmlRegisterType<GamePaintedItem>( "linjesuxus.game", 1, 0, "Game" );
    view.connect( view.engine(), SIGNAL(quit()), &app, SLOT(quit()) );
    view.setSource( QUrl( "qrc:/src/main.qml" ) );
    view.setResizeMode( QQuickView::SizeRootObjectToView );
    view.show();
    return app.exec();
}
