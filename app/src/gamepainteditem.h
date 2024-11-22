#ifndef GAMEPAINTEDITEM_H
#define GAMEPAINTEDITEM_H

#include <QQmlEngine>
#include <QQuickPaintedItem>

class GameCore;

class GamePaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    GamePaintedItem();
    ~GamePaintedItem();
    void paint(QPainter *painter);
    void mousePressEvent(QMouseEvent *event);

protected:
    void drawGrid(QPainter *painter, const qreal &cellWidth, const qreal &cellHeight);
    void drawCells(QPainter *painter, const qreal &cellWidth, const qreal &cellHeight);
    qreal getCellWidth() const;
    qreal getCellHeight() const;

public:
    static void setWidth(const uint &newWidth = 3);
    static void setHeight(const uint &newHeight = 3);
    static void setWinLength(const uint &newWinLength = 3);
    static void setFirstPlayer(const uint &newFirstPlayer = 1);
    static void setPlayers(const uint &newPlayers = 2);

protected:
    static uint &getWidth();
    static uint &getHeight();
    static uint &getWinLength();
    static uint &getFirstPlayer();
    static uint &getPlayers();

    GameCore *m_pGame = nullptr;
    QList<QImage*> m_nPlayersPic;

    static uint m_sWidth;
    static uint m_sHeight;
    static uint m_sWinLength;
    static uint m_sFirstPlayer;
    static uint m_sPlayers;
};

#endif // GAMEPAINTEDITEM_H
