#include <QTest>
#include "../src/game.h"

class Test_Game : public QObject
{
    Q_OBJECT
private slots:
    void move_data();
    void move();

};
