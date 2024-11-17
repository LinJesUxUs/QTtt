#include <QTest>
#include <directions.h>

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

void TestDirections::getDirection_data()
{
    QTest::addColumn<Directions::Direction>("direction");
    QTest::addColumn<int>("resultWidth");
    QTest::addColumn<int>("resultHeight");
    QTest::newRow("getDirection_test1") << Directions::Direction::Horizontal << 1 << 0;
    QTest::newRow("getDirection_test2") << Directions::Direction::Vertical << 0 << 1;
    QTest::newRow("getDirection_test3") << Directions::Direction::BSlash << 1 << 1;
    QTest::newRow("getDirection_test4") << Directions::Direction::FSlash << -1 << 1;
}

void TestDirections::getDirection()
{
    QFETCH(Directions::Direction,direction);
    QFETCH(int,resultWidth);
    QFETCH(int,resultHeight);
    QCOMPARE(Directions::getDirection(direction), QSize(resultWidth, resultHeight ) );
}

void TestDirections::negative_data()
{
    QTest::addColumn<int>("Width");
    QTest::addColumn<int>("Height");
    QTest::addColumn<int>("resultWidth");
    QTest::addColumn<int>("resultHeight");
    QTest::newRow("negative_test1") <<  1 << 0 <<  -1 << 0;
    QTest::newRow("negative_test2") <<  0 << 1 <<  0 << -1;
    QTest::newRow("negative_test3") <<  1 << 1 <<  -1 << -1;
    QTest::newRow("negative_test4") << -1 << 1 << 1 << -1;
}

void TestDirections::negative()
{
    QFETCH(int,Width);
    QFETCH(int,Height);
    QFETCH(int,resultWidth);
    QFETCH(int,resultHeight);
    QCOMPARE(Directions::negative(QSize(Width, Height )), QSize(resultWidth, resultHeight ) );
}

void TestDirections::getList()
{
    QList<QSize> lst = Directions::getList();
    QCOMPARE(lst.front(), Directions::getDirection(Directions::Direction::Horizontal) );
    lst.pop_front();
    QCOMPARE(lst.front(), Directions::getDirection(Directions::Direction::Vertical) );
    lst.pop_front();
    QCOMPARE(lst.front(), Directions::getDirection(Directions::Direction::BSlash) );
    lst.pop_front();
    QCOMPARE(lst.front(), Directions::getDirection(Directions::Direction::FSlash) );
    lst.pop_front();
}

QTEST_MAIN(TestDirections)
#include "TestDirections.moc"
