#include "test_game.h"

void Test_Game::move_data()
{
    QTest::addColumn<int>("width");
    QTest::addColumn<int>("height");
    QTest::addColumn<int>("m1x");
    QTest::addColumn<int>("m1y");
    QTest::addColumn<int>("p1");
    QTest::addColumn<int>("f1");
    QTest::addColumn<int>("m2x");
    QTest::addColumn<int>("m2y");
    QTest::addColumn<int>("p2");
    QTest::addColumn<int>("f2");
    QTest::newRow("move_test1") << 3 << 3
                                << 0 << 0 << 1 << 1
                                << 2 << 2 << 2 << 2;
    QTest::newRow("move_test2") << 3 << 3
                                << 0 << 1 << 2 << 2
                                << 1 << 1 << 1 << 1;
    QTest::newRow("move_test3") << 3 << 3
                                << 0 << 2 << 2 << 2
                                << 1 << 2 << 1 << 1;
    QTest::newRow("move_test4") << 3 << 3
                                << 1 << 0 << 1 << 1
                                << 2 << 0 << 2 << 2;
    QTest::newRow("move_test5") << 3 << 3
                                << 2 << 1 << 1 << 1
                                << 2 << 1 << 2 << 1;
    QTest::newRow("move_test6") << 1 << 1
                                << 2 << 1 << 1 << 0
                                << -2 << 1 << -1 << 0;
}

void Test_Game::move()
{
    QFETCH(int,width);
    QFETCH(int,height);
    QFETCH(int,m1x);
    QFETCH(int,m1y);
    QFETCH(int,p1);
    QFETCH(int,f1);
    QFETCH(int,m2x);
    QFETCH(int,m2y);
    QFETCH(int,p2);
    QFETCH(int,f2);
    uint retVal;
    Game game(QSize(width,height),3,p1);
    game.move(QSize(m1x,m1y),p1);
    try {
        retVal = game.getField(QSize(m1x,m1y)); }
    catch (const char* err_msg) {
        retVal = 0; }
    QCOMPARE(retVal,(uint)f1);
    game.move(QSize(m2x,m2y),p2);
    try {
        retVal = game.getField(QSize(m2x,m2y)); }
    catch (const char* err_msg) {
        retVal = 0; }
    QCOMPARE(retVal,(uint)f2);
}

void Test_Game::getWinLength_data()
{
    QTest::addColumn<int>("width");
    QTest::addColumn<int>("height");
    QTest::addColumn<int>("winLength");
    QTest::newRow("winLength_test-1") << 3 << 3 << -1 ;
    QTest::newRow("winLength_test0") << 3 << 3 << 0 ;
    QTest::newRow("winLength_test1") << 3 << 3 << 1 ;
    QTest::newRow("winLength_test2") << 3 << 3 << 4 ;
    QTest::newRow("winLength_test3") << 3 << 4 << 4 ;
    QTest::newRow("winLength_test4") << 4 << 4 << 4 ;
}

void Test_Game::getWinLength()
{
    QFETCH(int,width);
    QFETCH(int,height);
    QFETCH(int,winLength);
    Game game(QSize(width,height),winLength);
    if ( winLength < 1 )
        QCOMPARE(game.getWinLength(), uint(1) );
    else if ( width < height )
        QCOMPARE(game.getWinLength(), uint(winLength>width ?width :winLength) );
    else
        QCOMPARE(game.getWinLength(), uint(winLength>height ?height :winLength) );
}

void Test_Game::getNPlayers_data()
{
    QTest::addColumn<int>("width");
    QTest::addColumn<int>("height");
    QTest::addColumn<int>("nPlayers");
    QTest::newRow("nPlayers_test-1") << 3 << 3 << -1 ;
    QTest::newRow("nPlayers_test0") << 3 << 3 << 0 ;
    QTest::newRow("nPlayers_test1") << 3 << 3 << 1 ;
    QTest::newRow("nPlayers_test2") << 3 << 3 << 2 ;
    QTest::newRow("nPlayers_test3") << 3 << 3 << 3 ;
    QTest::newRow("nPlayers_test4") << 3 << 3 << 4 ;
}

void Test_Game::getNPlayers()
{
    QFETCH(int,width);
    QFETCH(int,height);
    QFETCH(int,nPlayers);
    Game game(QSize(width,height),3,1,nPlayers);
    QCOMPARE(game.getNPlayers(), uint(nPlayers<0?0:nPlayers) );
}

void Test_Game::fieldSize_data()
{
    QTest::addColumn<int>("width");
    QTest::addColumn<int>("height");
    QTest::newRow("fieldSize_test0") << 0 << 0 ;
    QTest::newRow("fieldSize_test1") << 1 << 0 ;
    QTest::newRow("fieldSize_test2") << -1 << 1 ;
    QTest::newRow("fieldSize_test3") << 1 << 1 ;
    QTest::newRow("fieldSize_test4") << 2 << 2 ;
    QTest::newRow("fieldSize_test5") << 3 << 3 ;
    QTest::newRow("fieldSize_test6") << 1 << 1000 ;
    QTest::newRow("fieldSize_test7") << 1000 << 1000 ;
}

void Test_Game::fieldSize()
{
    QFETCH(int,width);
    QFETCH(int,height);
    Game game(QSize(width,height));
    QCOMPARE(game.getWidth(),uint(width < 1 ? 1 : width) );
    QCOMPARE(game.getHeight(),uint(height < 1 ? 1 : height) );
}

QTEST_MAIN(Test_Game)
