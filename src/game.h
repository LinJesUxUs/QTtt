#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QList>

class Game : public QObject
{
    Q_OBJECT
private:
    const uint nWinLength;
    const uint nPlayers;
    uint nTurn;
    QList<QList<uint>> m_nField;

public:
    Game(const QSize &field, const uint &winLength = 3, const uint firstPlayer = 1, const uint players = 2, QObject *parent = 0);

private:
    void isEnd(const QSize &pos) const;
    bool isWinRange(const QSize &begin, const QSize &end) const;
    const QSize vecLen(const QSize &pos, const int xOff, const int yOff) const;

    inline bool isBusy(const QSize &pos) const;
    inline bool isOutOfRange(const QSize &pos) const;
    inline bool isOutOfRange(const uint w, const uint h) const;

    inline void nextTurn();

public:
    const uint &getNWinLength() const;
    const uint &getNPlayers() const;
    uint getField(const QSize &pos) const;
    uint getField(const uint w, const uint h) const;

public slots:

    void move(const QSize &pos, const uint &player);

signals:
    void onMove(const QSize &pos, const uint &player);
    void onEnd(const QSize &posBegin, const QSize &posEnd, const uint &player) const;

};

#endif // GAME_H
