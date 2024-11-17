#include <QTest>
#include <gamecore.h>

class TestGameCore : public QObject
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

void TestGameCore::move_data()
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

void TestGameCore::move()
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
    GameCore game(QSize(width,height),3,p1);
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

void TestGameCore::getWinLength_data()
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

void TestGameCore::getWinLength()
{
    QFETCH(int,width);
    QFETCH(int,height);
    QFETCH(int,winLength);
    GameCore game(QSize(width,height),winLength);
    if ( winLength < 1 )
        QCOMPARE(game.getWinLength(), uint(1) );
    else if ( width < height )
        QCOMPARE(game.getWinLength(), uint(winLength>width ?width :winLength) );
    else
        QCOMPARE(game.getWinLength(), uint(winLength>height ?height :winLength) );
}

void TestGameCore::getNPlayers_data()
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

void TestGameCore::getNPlayers()
{
    QFETCH(int,width);
    QFETCH(int,height);
    QFETCH(int,nPlayers);
    GameCore game(QSize(width,height),3,1,nPlayers);
    QCOMPARE(game.getNPlayers(), uint(nPlayers<0?0:nPlayers) );
}

void TestGameCore::fieldSize_data()
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

void TestGameCore::fieldSize()
{
    QFETCH(int,width);
    QFETCH(int,height);
    GameCore game(QSize(width,height));
    QCOMPARE(game.getWidth(),uint(width < 1 ? 1 : width) );
    QCOMPARE(game.getHeight(),uint(height < 1 ? 1 : height) );
}

void TestGameCore::onEnd_data()
{
    QTest::addColumn<int>("size");
    QTest::addColumn<int>("m1x");
    QTest::addColumn<int>("m1y");
    QTest::addColumn<int>("m2x");
    QTest::addColumn<int>("m2y");
    QTest::addColumn<int>("m3x");
    QTest::addColumn<int>("m3y");
    QTest::addColumn<int>("m4x");
    QTest::addColumn<int>("m4y");
    QTest::addColumn<int>("m5x");
    QTest::addColumn<int>("m5y");
    QTest::newRow("end_2x2_test1") << 2
                                    << 0 << 0 << 1 << 0
                                    << 0 << 1 << 0 << 0 << 0 << 0;
    QTest::newRow("end_2x2_test2") << 2
                                    << 1 << 0 << 0 << 0
                                    << 1 << 1 << 0 << 0 << 0 << 0;
    QTest::newRow("end_2x2_test3") << 2
                                    << 0 << 0 << 0 << 1
                                    << 1 << 0 << 0 << 0 << 0 << 0;
    QTest::newRow("end_2x2_test4") << 2
                                    << 0 << 1 << 0 << 0
                                    << 1 << 1 << 0 << 0 << 0 << 0;
    QTest::newRow("end_2x2_test5") << 2
                                    << 0 << 0 << 0 << 1
                                    << 1 << 1 << 0 << 0 << 0 << 0;
    QTest::newRow("end_2x2_test6") << 2
                                    << 0 << 1 << 0 << 0
                                    << 1 << 0 << 0 << 0 << 0 << 0;

    QTest::newRow("end_3x3_test2") << 3
                                    << 0 << 0 << 1 << 0
                                    << 0 << 1 << 1 << 1
                                    << 0 << 2 ;
    QTest::newRow("end_3x3_test2") << 3
                                    << 1 << 0 << 2 << 0
                                    << 1 << 1 << 2 << 1
                                    << 1 << 2 ;
    QTest::newRow("end_3x3_test3") << 3
                                    << 2 << 0 << 1 << 0
                                    << 2 << 1 << 1 << 1
                                    << 2 << 2 ;
    QTest::newRow("end_3x3_test4") << 3
                                    << 0 << 0 << 0 << 1
                                    << 1 << 0 << 1 << 1
                                    << 2 << 0 ;
    QTest::newRow("end_3x3_test5") << 3
                                    << 0 << 1 << 0 << 0
                                    << 1 << 1 << 1 << 0
                                    << 2 << 1 ;
    QTest::newRow("end_3x3_test6") << 3
                                    << 0 << 2 << 0 << 0
                                    << 1 << 2 << 1 << 0
                                    << 2 << 2 ;
    QTest::newRow("end_3x3_test7") << 3
                                    << 0 << 0 << 0 << 1
                                    << 1 << 1 << 1 << 0
                                    << 2 << 2 ;
    QTest::newRow("end_3x3_test8") << 3
                                    << 0 << 2 << 0 << 0
                                    << 1 << 1 << 1 << 0
                                    << 2 << 0 ;
}

void TestGameCore::onEnd()
{
    QFETCH(int,size);
    QFETCH(int,m1x);
    QFETCH(int,m1y);
    QFETCH(int,m2x);
    QFETCH(int,m2y);
    QFETCH(int,m3x);
    QFETCH(int,m3y);
    QFETCH(int,m4x);
    QFETCH(int,m4y);
    QFETCH(int,m5x);
    QFETCH(int,m5y);
    GameCore game(QSize(size,size),size);
    game.move(QSize(m1x,m1y),1);
    game.move(QSize(m2x,m2y),2);
    game.move(QSize(m3x,m3y),1);
    if (size>2) {
        game.move(QSize(m4x,m4y),2);
        game.move(QSize(m5x,m5y),1);
        QCOMPARE(true,true);
    }
    else
        QCOMPARE(true,true);
}

QTEST_MAIN(TestGameCore)
#include "TestGameCore.moc"
