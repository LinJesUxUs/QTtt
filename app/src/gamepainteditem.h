// Copyright (C) 2026 Radik Mirgaliev <radikru96@gmail.com>
//
// This file is part of QTtt project.
// Licensed under the GPLv3.
// See the LICENSE file in the project root for more information.

/**
 * @file gamepainteditem.h
 * @brief Visual representation of the game board.
 * @details Uses QPainter to render the grid, player icons, and the winning line.
 */

#ifndef GAMEPAINTEDITEM_H
#define GAMEPAINTEDITEM_H

#include <QQuickPaintedItem>

class SettingsProxy;
class GameCore;

/**
 * @struct EndValue
 * @brief Container for end-of-game state.
 * @details Stores the coordinates of the winning line and the ID of the winner.
 */
struct EndValue {
    QSize beginPos; ///< Start coordinate of the winning sequence.
    QSize endPos; ///< End coordinate of the winning sequence.
    uint winPlayer; ///< ID of the winning player (0 for draw).
};

/**
 * @class GamePaintedItem
 * @brief Custom QQuickItem for rendering the Tic-Tac-Toe board.
 *
 * This class translates GameCore logic into visual pixels. It handles
 * mouse input to trigger moves and uses QPainter for custom drawing.
 */
class GamePaintedItem : public QQuickPaintedItem {
    Q_OBJECT
    QML_ELEMENT

    /** @name QML Properties
     *  Properties exposed for data binding in QML.
     *  @{ */
    Q_PROPERTY(QString gameState READ gameState NOTIFY gameStateChanged)
    Q_PROPERTY(uint fieldWidth READ fieldWidth NOTIFY fieldWidthChanged)
    Q_PROPERTY(uint fieldHeight READ fieldHeight NOTIFY fieldHeightChanged)
    /** @} */

protected:
    static SettingsProxy* m_SpSettingsProxy; ///< Shared pointer to settings for image and size config.

public:
    /** @brief Returns the global settings proxy. */
    static SettingsProxy* getSpSettingsProxy();

    /** @brief Assigns the global settings proxy used for rendering resources. */
    static void setSpSettingsProxy(SettingsProxy* newSpSettingsProxy);

public:
    /** @brief Initializes the item, loads textures, and creates a new GameCore instance. */
    GamePaintedItem();

    /** @brief Cleans up game engine and allocated resources. */
    ~GamePaintedItem();

    /**
     * @brief Resets the game state and clears the board.
     * @note Callable from QML.
     */
    Q_INVOKABLE void restart();

    /**
     * @brief Provides the current game status description.
     * @note Callable from QML.
     */
    Q_INVOKABLE QString gameState();

    /** @return Current grid width from GameCore. */
    uint fieldWidth();

    /** @return Current grid height from GameCore. */
    uint fieldHeight();

    /** @brief Handles mouse press to capture the starting point of a click. */
    void mousePressEvent(QMouseEvent* event) override;

    /** @brief Handles mouse release to calculate which cell was clicked and attempt a move. */
    void mouseReleaseEvent(QMouseEvent* event) override;

    /** @brief Main rendering method for the game board. */
    void paint(QPainter* painter) override;

protected slots:
    /** @brief Internal handler for successful move signals. Triggers an update(). */
    void onMove(const QSize&, const uint&);

    /** @brief Internal handler for game end. Prepares the winning line for drawing. */
    void onEnd(const QSize& posBegin, const QSize& posEnd, const uint& player);

Q_SIGNALS:
    void gameStateChanged();
    void fieldWidthChanged();
    void fieldHeightChanged();

protected:
    /** @name Internal Drawing Helpers
     *  Used inside the paint() method.
     *  @{ */

    /** @brief Renders the background grid lines. */
    inline void drawGrid(QPainter* painter, const qreal& cellWidth, const qreal& cellHeight);

    /** @brief Renders player icons in occupied cells. */
    inline void drawCells(QPainter* painter, const qreal& cellWidth, const qreal& cellHeight);

    /** @brief Renders the winning line or strike-through at the end of the game. */
    inline void drawEnd(QPainter* painter);
    /** @} */

    /** @return Calculated width of a single cell based on item size. */
    qreal getCellWidth() const;

    /** @return Calculated height of a single cell based on item size. */
    qreal getCellHeight() const;

    GameCore* m_pGame = nullptr; ///< Pointer to the logical game engine.
    EndValue* m_pEndValue = nullptr; ///< Stores win data when the game is over.
    QSize m_mousePressPoint; ///< Temporary storage for click coordinate.

    QList<QString*> m_nLocalPlayers; ///< @internal Future feature for player management.
    QList<QImage*> m_nPlayersPic; ///< Cached icons for active turns.
    QList<QImage*> m_nWinPlayersPic; ///< Cached icons for winning state.
    QList<QUrl*> m_nGameStatePic; ///< Image URLs for UI status displays.
};

#endif // GAMEPAINTEDITEM_H
