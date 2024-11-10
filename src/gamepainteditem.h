#ifndef GAMEPAINTEDITEM_H
#define GAMEPAINTEDITEM_H

#include <QQmlEngine>
#include <QQuickPaintedItem>

class Game;

class GamePaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    GamePaintedItem();
    ~GamePaintedItem();
    void paint(QPainter *painter);

    static void setWidth(uint &newWidth = 3);
    static void setHeight(uint &newHeight = 3);
    static void setWinLength(uint &newWinLength = 3);
    static void setFirstPlayer(uint &newFirstPlayer = 1);
    static void setPlayers(uint &newPlayers = 2);

protected:
    static uint &getWidth() const;
    static uint &getHeight() const;
    static uint &getWinLength() const;
    static uint &getFirstPlayer() const;
    static uint &getPlayers() const;

    void drawGrid(QPainter *painter);
    void drawCells(QPainter *painter);

    Game *m_pGame = nullptr;
    QList<QImage*> m_nPlayersPic;

    static uint mWidth = 3;
    static uint mHeight = 3;
    static uint mWinLength = 3;
    static uint mFirstPlayer = 1;
    static uint mPlayers = 2;
};

#endif // GAMEPAINTEDITEM_H
