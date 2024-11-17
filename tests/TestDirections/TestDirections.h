#include <QTest>
#include "../src/directions.h"

class TestDirections : public QObject
{
    Q_OBJECT
private slots:
    void getDirection_data();
    void getDirection();
    void negative_data();
    void negative();
    void getList();
};
