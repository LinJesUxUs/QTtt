#ifndef GAMEPAINTEDITEM_H
#define GAMEPAINTEDITEM_H

#include <QQmlEngine>
#include <QQuickPaintedItem>

class GameCore;

struct EndValue {
    QSize beginPos;
    QSize endPos;
    uint winPlayer;
};

class GamePaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString gameState READ gameState NOTIFY gameStateChanged)
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

    static uint m_sWidth;
    static uint m_sHeight;
    static uint m_sWinLength;
    static uint m_sFirstPlayer;
    static uint m_sPlayers;

public:
    GamePaintedItem();
    ~GamePaintedItem();
    Q_INVOKABLE void restart();
    Q_INVOKABLE QString gameState();
    void mousePressEvent(QMouseEvent *event);
    void paint(QPainter *painter);

protected slots:
    void onMove(const QSize &pos, const uint &player);
    void onEnd(const QSize &posBegin, const QSize &posEnd, const uint &player);

Q_SIGNALS:
    void gameStateChanged();

protected:
    inline void drawGrid(QPainter *painter, const qreal &cellWidth, const qreal &cellHeight);
    inline void drawCells(QPainter *painter, const qreal &cellWidth, const qreal &cellHeight);
    inline void drawEnd(QPainter *painter);
    qreal getCellWidth() const;
    qreal getCellHeight() const;

    GameCore *m_pGame = nullptr;
    EndValue *m_pEndValue = nullptr;
    QList<QString*> m_nLocalPlayers; // Feature for future
    QList<QImage*> m_nPlayersPic;
    QList<QImage*> m_nWinPlayersPic;
};

#endif // GAMEPAINTEDITEM_H
