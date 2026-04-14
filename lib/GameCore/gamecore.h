// Copyright (C) 2026 Radik Mirgaliev <radikru96@gmail.com>
//
// This file is part of QTtt project.
// Licensed under the GPLv3.
// See the LICENSE file in the project root for more information.

/**
 * @file gamecore.h
 * @brief The heart of the Tic-Tac-Toe logic.
 * @details Handles the game board, turn switching, and win condition checking.
 */

#ifndef GAMECORE_H
#define GAMECORE_H

#include <QList>
#include <QObject>

/**
 * @class GameCore
 * @brief Manages game state and enforces rules.
 *
 * This class maintains the 2D grid, tracks which player's turn it is,
 * and emits signals when moves occur or the game ends.
 */
class GameCore : public QObject {
    Q_OBJECT
private:
    uint mTurn; ///< Current player ID whose turn it is.
    uint mTurnCount = 0; ///< Total moves made to detect a draw.
    QList<QList<uint>> m_nField; ///< 2D grid representing the board (0 = empty).
    uint mWinLength; ///< Number of consecutive marks needed to win.
    uint mPlayers; ///< Total number of players in the session.

public:
    /**
     * @brief Constructs a new GameCore session.
     * @param field Size of the game board (width and height).
     * @param winLength Sequence length required for a win (default: 3).
     * @param firstPlayer ID of the player who starts (default: 1).
     * @param players Total count of players (default: 2).
     * @param parent Qt parent object.
     */
    GameCore(const QSize& field, const uint& winLength = 3, const uint& firstPlayer = 1, const uint& players = 2, QObject* parent = 0);

private:
    /**
     * @brief Checks if the last move at 'pos' ended the game.
     * @param pos The coordinate of the last placed mark.
     */
    void isEnd(const QSize& pos) const;

    /**
     * @brief Validates if the distance between two points matches the win length.
     * @param begin Start of the winning line.
     * @param end End of the winning line.
     * @return true if the range length equals mWinLength.
     */
    bool isWinRange(const QSize& begin, const QSize& end) const;

    /**
     * @brief Calculates how far a player's line extends in a specific direction.
     * @param pos Start position.
     * @param offset Direction vector.
     * @return The furthest coordinate with the same player ID.
     */
    const QSize vecLen(const QSize& pos, const QSize& offset) const;

    /**
     * @brief Overloaded version of vecLen using raw X/Y offsets.
     */
    const QSize vecLen(const QSize& pos, const int xOffset, const int yOffset) const;

    /** @brief Checks if a cell is already taken. */
    inline bool isBusy(const QSize& pos) const;

    /** @brief Checks if coordinates are outside the board boundaries. */
    inline bool isOutOfRange(const QSize& pos) const;

    /** @brief Checks if raw W/H coordinates are outside the board boundaries. */
    inline bool isOutOfRange(const uint w, const uint h) const;

    /** @brief Increments the turn counter and wraps around if needed. */
    inline void nextTurn();

public:
    /** @return Number of marks required to win. */
    const uint& getWinLength() const;

    /** @return Total number of players. */
    const uint& getNPlayers() const;

    /** @return Board width. */
    uint getWidth() const;

    /** @return Board height. */
    uint getHeight() const;

    /**
     * @brief Gets player ID at a specific position.
     * @throw const char* "Out of range!" if position is invalid.
     */
    uint getField(const QSize& pos) const;

    /**
     * @brief Gets player ID using raw coordinates.
     * @throw const char* "Out of range!" if coordinates are invalid.
     */
    uint getField(const uint w, const uint h) const;

    /** @return Current player ID or 0 if the game is a draw. */
    uint turn() const;

public slots:
    /**
     * @brief Attempts to place a player's mark on the board.
     * @param pos Target coordinates.
     * @param player ID of the player making the move.
     */
    void move(const QSize& pos, const uint& player);

signals:
    /** @brief Emitted when a valid move is processed. */
    void onMove(const QSize& pos, const uint& player);

    /** @brief Emitted when a move is rejected (cell busy, out of range, or wrong turn). */
    void onNoMove(const QSize& pos, const uint& player);

    /**
     * @brief Emitted when the game finishes.
     * @param posBegin Start of the winning line (empty QSize if draw).
     * @param posEnd End of the winning line (empty QSize if draw).
     * @param player Winner ID (0 if draw).
     */
    void onEnd(const QSize& posBegin, const QSize& posEnd, const uint& player) const;
};

#endif // GAMECORE_H
