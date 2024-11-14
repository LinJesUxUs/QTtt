#include <QTest>
#include "../src/game.h"

class Test_Game : public QObject
{
    Q_OBJECT
private slots:
    void move_data();
    void move();
    void getWinLength_data();
    void getWinLength();
    void getNPlayers_data();
    void getNPlayers();
    void fieldSize_data();
    void fieldSize();
    void onEnd_data();
    void onEnd();

};
