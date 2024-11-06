#ifndef GAMEPAINTEDITEM_H
#define GAMEPAINTEDITEM_H

#include <QQmlEngine>
#include <QQuickPaintedItem>

class GamePaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    GamePaintedItem();
};

#endif // GAMEPAINTEDITEM_H
