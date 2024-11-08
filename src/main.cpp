#include "gamePaintedItem.h"
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlFileSelector>
#include <QQuickView>
#include <QDir>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView view;
    QFileInfo fi( app.applicationFilePath() );
    app.setApplicationName( fi.baseName() );
    qmlRegisterType<GamePaintedItem>( "linjesuxus.game", 1, 0, "Game" );
    view.connect( view.engine(), SIGNAL(quit()), &app, SLOT(quit()) );
    view.setSource( QUrl( "qrc:/src/main.qml" ) );
    view.setResizeMode( QQuickView::SizeRootObjectToView );
    view.show();
    return app.exec();
}
