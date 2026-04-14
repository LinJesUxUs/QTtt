// Copyright (C) 2026 Radik Mirgaliev <radikru96@gmail.com>
//
// This file is part of QTtt project.
// Licensed under the GPLv3.
// See the LICENSE file in the project root for more information.

/**
 * @file TestDirections.cpp
 * @brief Unit tests for the Directions utility class.
 * @details Ensures that coordinate offsets for all 2D grid directions
 * (horizontal, vertical, and diagonals) are correctly defined and reversible.
 */

#include <QTest>
#include <directions.h>

/**
 * @class TestDirections
 * @brief Test suite for validating grid navigation vectors.
 */
class TestDirections : public QObject {
    Q_OBJECT
private slots:
    /**
     * @brief Provides mapping between Direction enums and expected QSize offsets.
     */
    void getDirection_data();

    /**
     * @brief Tests the conversion of Direction enums to coordinate vectors.
     * @test Verifies that each enum returns the correct (x, y) step.
     */
    void getDirection();

    /**
     * @brief Provides sample vectors for inversion testing.
     */
    void negative_data();

    /**
     * @brief Tests the vector inversion logic.
     * @test Ensures that @ref Directions::negative correctly flips the sign of both coordinates.
     */
    void negative();

    /**
     * @brief Validates the complete list of available directions.
     * @test Checks that @ref Directions::getList returns all 4 primary directions in the correct order.
     */
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
    QFETCH(Directions::Direction, direction);
    QFETCH(int, resultWidth);
    QFETCH(int, resultHeight);
    QCOMPARE(Directions::getDirection(direction), QSize(resultWidth, resultHeight));
}

void TestDirections::negative_data()
{
    QTest::addColumn<int>("Width");
    QTest::addColumn<int>("Height");
    QTest::addColumn<int>("resultWidth");
    QTest::addColumn<int>("resultHeight");
    QTest::newRow("negative_test1") << 1 << 0 << -1 << 0;
    QTest::newRow("negative_test2") << 0 << 1 << 0 << -1;
    QTest::newRow("negative_test3") << 1 << 1 << -1 << -1;
    QTest::newRow("negative_test4") << -1 << 1 << 1 << -1;
}

void TestDirections::negative()
{
    QFETCH(int, Width);
    QFETCH(int, Height);
    QFETCH(int, resultWidth);
    QFETCH(int, resultHeight);
    QCOMPARE(Directions::negative(QSize(Width, Height)), QSize(resultWidth, resultHeight));
}

void TestDirections::getList()
{
    QList<QSize> lst = Directions::getList();
    QCOMPARE(lst.front(), Directions::getDirection(Directions::Direction::Horizontal));
    lst.pop_front();
    QCOMPARE(lst.front(), Directions::getDirection(Directions::Direction::Vertical));
    lst.pop_front();
    QCOMPARE(lst.front(), Directions::getDirection(Directions::Direction::BSlash));
    lst.pop_front();
    QCOMPARE(lst.front(), Directions::getDirection(Directions::Direction::FSlash));
    lst.pop_front();
}

QTEST_MAIN(TestDirections)
#include "TestDirections.moc"
