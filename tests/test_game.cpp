#include "test_game.h"

void Test_Game::move_data()
{
    QTest::addColumn<int>("w");
    QTest::addColumn<int>("h");
    QTest::addColumn<int>("m1x");
    QTest::addColumn<int>("m1y");
    QTest::addColumn<int>("p1");
    QTest::addColumn<int>("m2x");
    QTest::addColumn<int>("m2y");
    QTest::addColumn<int>("p2");
    QTest::newRow("move_test1") << 3 << 3
                                << 0 << 0 << 1
                                << 2 << 2 << 2;
    QTest::newRow("move_test2") << 3 << 3
                                << 0 << 1 << 2
                                << 1 << 1 << 1;
    QTest::newRow("move_test3fail") << 3 << 3
                                << 0 << 1 << 2
                                << 0 << 1 << 2;
}

void Test_Game::move()
{
    QFETCH(int,w);
    QFETCH(int,h);
    QFETCH(int,m1x);
    QFETCH(int,m1y);
    QFETCH(int,p1);
    QFETCH(int,m2x);
    QFETCH(int,m2y);
    QFETCH(int,p2);
    Game game(QSize(w,h),3,p1);
    game.move(QSize(m1x,m1y),p1);
    QCOMPARE(game.getField(QSize(m1x,m1y)),(uint)p1);
    game.move(QSize(m2x,m2y),p2);
    QCOMPARE(game.getField(QSize(m2x,m2y)),(uint)p2);
}

QTEST_MAIN(Test_Game)
