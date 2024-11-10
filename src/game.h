#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QList>

class Game : public QObject
{
    Q_OBJECT
private:
    uint mTurn;
    QList<QList<uint>> m_nField;

public:
    const uint WIN_LENGTH;
    const uint PLAYERS;

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
    const uint &getWidth() const;
    const uint &getHeight() const;
    uint getField(const QSize &pos) const;
    uint getField(const uint w, const uint h) const;

public slots:

    void move(const QSize &pos, const uint &player);

signals:
    void onMove(const QSize &pos, const uint &player);
    void onEnd(const QSize &posBegin, const QSize &posEnd, const uint &player);

};

#endif // GAME_H
