// Copyright (C) 2026 Radik Mirgaliev <radikru96@gmail.com>
//
// This file is part of QTtt project.
// Licensed under the GPLv3.
// See the LICENSE file in the project root for more information.

/**
 * @file TestGameCore.cpp
 * @brief Unit tests for the GameCore logic.
 * @details Validates game board initialization, move validation, player switching,
 * and win condition detection using the Qt Test framework.
 */

#include <QSignalSpy>
#include <QTest>
#include <gamecore.h>

/**
 * @class TestGameCore
 * @brief Test suite for the GameCore class.
 * @details Contains various test cases to ensure the stability of the game engine.
 */
class TestGameCore : public QObject {
    Q_OBJECT
private slots:
    /**
     * @brief Data provider for the move() test.
     * @test Defines board sizes and sequences of moves (valid/invalid).
     */
    void move_data();

    /**
     * @brief Tests the move() functionality and onMove/onNoMove signals.
     * @test Verifies that players can only move in their turn and within board bounds.
     */
    void move();

    /**
     * @brief Data provider for win length validation.
     */
    void getWinLength_data();

    /**
     * @brief Tests that winLength is correctly clamped by board dimensions.
     * @test Ensures winLength is never 0 and not larger than the field size.
     */
    void getWinLength();

    /**
     * @brief Data provider for player count validation.
     */
    void getNPlayers_data();

    /**
     * @brief Tests player count initialization.
     * @test Verifies that the game correctly stores the number of players.
     */
    void getNPlayers();

    /**
     * @brief Data provider for field size validation.
     */
    void fieldSize_data();

    /**
     * @brief Tests board boundary logic.
     * @test Ensures that even with invalid input (0 or negative), the field is at least 1x1.
     */
    void fieldSize();

    /**
     * @brief Data provider for endgame scenarios.
     */
    void onEnd_data();

    /**
     * @brief Tests the onEnd signal emission.
     * @test Verifies that the game detects a win or draw and emits onEnd exactly once.
     */
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
    QFETCH(int, width);
    QFETCH(int, height);
    QFETCH(int, m1x);
    QFETCH(int, m1y);
    QFETCH(int, p1);
    QFETCH(int, f1);
    QFETCH(int, m2x);
    QFETCH(int, m2y);
    QFETCH(int, p2);
    QFETCH(int, f2);
    struct moves {
        QSize position;
        int player;
        int expected;
    };
    QList<moves> listMoves = { { QSize(m1x, m1y), p1, f1 },
        { QSize(m2x, m2y), p2, f2 } };
    uint retVal;
    GameCore* game = new GameCore(QSize(width, height), 3, listMoves[0].player);
    QList<QVariant> args;
    QSignalSpy spyMove(game, SIGNAL(onMove(QSize, uint)));
    QSignalSpy spyNoMove(game, SIGNAL(onNoMove(QSize, uint)));

    for (moves i : qAsConst(listMoves)) {
        game->move(i.position, i.player);

        try {
            retVal = game->getField(i.position);
        } catch (const char* err_msg) {
            retVal = 0;
        }
        QCOMPARE(retVal, (uint)i.expected);

        if (i.player == i.expected) {
            QCOMPARE(spyMove.count(), 1);
            args = spyMove.takeFirst();
        } else {
            QCOMPARE(spyNoMove.count(), 1);
            args = spyNoMove.takeFirst();
        }
        QCOMPARE(args.at(0).toSize(), i.position);
        QCOMPARE(args.at(1).toInt(), i.player);
    }
}

void TestGameCore::getWinLength_data()
{
    QTest::addColumn<int>("width");
    QTest::addColumn<int>("height");
    QTest::addColumn<int>("winLength");
    QTest::newRow("winLength_test-1") << 3 << 3 << -1;
    QTest::newRow("winLength_test0") << 3 << 3 << 0;
    QTest::newRow("winLength_test1") << 3 << 3 << 1;
    QTest::newRow("winLength_test2") << 3 << 3 << 4;
    QTest::newRow("winLength_test3") << 3 << 4 << 4;
    QTest::newRow("winLength_test4") << 4 << 4 << 4;
}

void TestGameCore::getWinLength()
{
    QFETCH(int, width);
    QFETCH(int, height);
    QFETCH(int, winLength);
    GameCore game(QSize(width, height), winLength);
    if (winLength < 1)
        QCOMPARE(game.getWinLength(), uint(1));
    else if (width < height)
        QCOMPARE(game.getWinLength(), uint(winLength > width ? width : winLength));
    else
        QCOMPARE(game.getWinLength(), uint(winLength > height ? height : winLength));
}

void TestGameCore::getNPlayers_data()
{
    QTest::addColumn<int>("width");
    QTest::addColumn<int>("height");
    QTest::addColumn<int>("nPlayers");
    QTest::newRow("nPlayers_test-1") << 3 << 3 << -1;
    QTest::newRow("nPlayers_test0") << 3 << 3 << 0;
    QTest::newRow("nPlayers_test1") << 3 << 3 << 1;
    QTest::newRow("nPlayers_test2") << 3 << 3 << 2;
    QTest::newRow("nPlayers_test3") << 3 << 3 << 3;
    QTest::newRow("nPlayers_test4") << 3 << 3 << 4;
}

void TestGameCore::getNPlayers()
{
    QFETCH(int, width);
    QFETCH(int, height);
    QFETCH(int, nPlayers);
    GameCore game(QSize(width, height), 3, 1, nPlayers);
    QCOMPARE(game.getNPlayers(), uint(nPlayers < 0 ? 0 : nPlayers));
}

void TestGameCore::fieldSize_data()
{
    QTest::addColumn<int>("width");
    QTest::addColumn<int>("height");
    QTest::newRow("fieldSize_test0") << 0 << 0;
    QTest::newRow("fieldSize_test1") << 1 << 0;
    QTest::newRow("fieldSize_test2") << -1 << 1;
    QTest::newRow("fieldSize_test3") << 1 << 1;
    QTest::newRow("fieldSize_test4") << 2 << 2;
    QTest::newRow("fieldSize_test5") << 3 << 3;
    QTest::newRow("fieldSize_test6") << 1 << 1000;
    QTest::newRow("fieldSize_test7") << 1000 << 1000;
}

void TestGameCore::fieldSize()
{
    QFETCH(int, width);
    QFETCH(int, height);
    GameCore game(QSize(width, height));
    QCOMPARE(game.getWidth(), uint(width < 1 ? 1 : width));
    QCOMPARE(game.getHeight(), uint(height < 1 ? 1 : height));
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
                                   << 0 << 2;
    QTest::newRow("end_3x3_test2") << 3
                                   << 1 << 0 << 2 << 0
                                   << 1 << 1 << 2 << 1
                                   << 1 << 2;
    QTest::newRow("end_3x3_test3") << 3
                                   << 2 << 0 << 1 << 0
                                   << 2 << 1 << 1 << 1
                                   << 2 << 2;
    QTest::newRow("end_3x3_test4") << 3
                                   << 0 << 0 << 0 << 1
                                   << 1 << 0 << 1 << 1
                                   << 2 << 0;
    QTest::newRow("end_3x3_test5") << 3
                                   << 0 << 1 << 0 << 0
                                   << 1 << 1 << 1 << 0
                                   << 2 << 1;
    QTest::newRow("end_3x3_test6") << 3
                                   << 0 << 2 << 0 << 0
                                   << 1 << 2 << 1 << 0
                                   << 2 << 2;
    QTest::newRow("end_3x3_test7") << 3
                                   << 0 << 0 << 0 << 1
                                   << 1 << 1 << 1 << 0
                                   << 2 << 2;
    QTest::newRow("end_3x3_test8") << 3
                                   << 0 << 2 << 0 << 0
                                   << 1 << 1 << 1 << 0
                                   << 2 << 0;
}

void TestGameCore::onEnd()
{
    QFETCH(int, size);
    QFETCH(int, m1x);
    QFETCH(int, m1y);
    QFETCH(int, m2x);
    QFETCH(int, m2y);
    QFETCH(int, m3x);
    QFETCH(int, m3y);
    QFETCH(int, m4x);
    QFETCH(int, m4y);
    QFETCH(int, m5x);
    QFETCH(int, m5y);
    GameCore* game = new GameCore(QSize(size, size), size);
    QSignalSpy spyEnd(game, SIGNAL(onEnd(QSize, QSize, uint)));
    game->move(QSize(m1x, m1y), 1);
    game->move(QSize(m2x, m2y), 2);
    game->move(QSize(m3x, m3y), 1);
    if (size > 2) {
        game->move(QSize(m4x, m4y), 2);
        game->move(QSize(m5x, m5y), 1);
    }
    QCOMPARE(spyEnd.count(), 1);
}

QTEST_MAIN(TestGameCore)
#include "TestGameCore.moc"
