// Copyright (C) 2026 Radik Mirgaliev <radikru96@gmail.com>
//
// This file is part of QTtt project.
// Licensed under the GPLv3.
// See the LICENSE file in the project root for more information.

/**
 * @file directions.h
 * @brief Helper class for managing 2D grid directions.
 * @details Provides coordinate offsets for horizontal, vertical, and diagonal movements.
 */

#ifndef DIRECTIONS_H
#define DIRECTIONS_H

#include <QList>
#include <QSize>

/**
 * @class Directions
 * @brief Utility class for grid navigation logic.
 */

class Directions {
public:
    /**
     * @enum Direction
     * @brief Predefined movement types on the game board.
     */
    enum class Direction {
        Horizontal, ///< From left to right (1, 0)
        Vertical, ///< From top to bottom (0, 1)
        BSlash, ///< Backslash diagonal: top-left to bottom-right (1, 1)
        FSlash ///< Forward slash diagonal: top-right to bottom-left (-1, 1)
    };

    /**
     * @brief Converts an enum Direction into a QSize offset.
     * @param direction Selected direction enum.
     * @return QSize Vector representing the step in X and Y coordinates.
     */
    static QSize getDirection(const Direction& direction);

    /**
     * @brief Inverts the given direction vector.
     * @param size The original direction vector.
     * @return QSize The opposite direction vector (e.g., (1,0) becomes (-1,0)).
     */
    static QSize negative(const QSize& size);

    /**
     * @brief Returns a list of all primary direction vectors.
     * @return QList<QSize> List containing Horizontal, Vertical, BSlash, and FSlash offsets.
     */
    static QList<QSize> getList();
};

#endif // DIRECTIONS_H
