#ifndef GAMEPAINTEDITEM_H
#define GAMEPAINTEDITEM_H

#include <QQmlEngine>
#include <QQuickPaintedItem>

class QSettings;
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
    GamePaintedItem();
    ~GamePaintedItem();
    Q_INVOKABLE void restart();
    Q_INVOKABLE QString gameState();
    void mousePressEvent(QMouseEvent *event);
    void paint(QPainter *painter);

protected slots:
    void onMove(const QSize &, const uint &);
    void onEnd(const QSize &posBegin, const QSize &posEnd, const uint &player);

Q_SIGNALS:
    void gameStateChanged();

protected:
    inline void drawGrid(QPainter *painter, const qreal &cellWidth, const qreal &cellHeight);
    inline void drawCells(QPainter *painter, const qreal &cellWidth, const qreal &cellHeight);
    inline void drawEnd(QPainter *painter);
    qreal getCellWidth() const;
    qreal getCellHeight() const;

    QSettings *settings = nullptr;
    GameCore *m_pGame = nullptr;
    EndValue *m_pEndValue = nullptr;
    QList<QString*> m_nLocalPlayers; // Feature for future
    QList<QImage*> m_nPlayersPic;
    QList<QImage*> m_nWinPlayersPic;
    QList<QUrl*> m_nGameStatePic;
};

#endif // GAMEPAINTEDITEM_H
