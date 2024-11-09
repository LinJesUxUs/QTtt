#ifndef GAMEPAINTEDITEM_H
#define GAMEPAINTEDITEM_H

#include <QQmlEngine>
#include <QQuickPaintedItem>

#define WIDTH 3
#define HEIGHT 3

class Game;

class GamePaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    GamePaintedItem();
    ~GamePaintedItem();
    void paint(QPainter *painter);

private:
    void drawGrid(QPainter *painter);
    Game *game = nullptr;
};

#endif // GAMEPAINTEDITEM_H
