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

    const bool isBusy(const QSize &pos) const;
    const bool isOutOfRange(const QSize &pos) const;
    const bool isOutOfRange(const uint w, const uint h) const;
    const bool isWinRange(const QSize &begin, const QSize &end) const;
    void isEnd(const QSize &pos) const;
    void nextTurn();
    const QSize &vecLen(const QSize &pos, const int xOff, const int yOff) const;

public:
    Game(const QSize &field = QSize(3,3), const uint &winLength = 3, const uint players = 2, QObject *parent = 0);

    const uint &getField(const QSize &pos) const;
    const uint &getField(const uint w, const uint h) const;
    const uint &getNWinLength() const;
    const uint &getNPlayers() const;

public slots:

    void move(const QSize &pos, const uint &player);

signals:
    void onMove(const QSize &pos, const uint &player);
    void onEnd(const QSize posBegin, const QSize posEnd, const uint player);

};

#endif // GAME_H
