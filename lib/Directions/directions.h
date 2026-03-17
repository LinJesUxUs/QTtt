// Copyright (C) 2026 Radik Mirgaliev <radikru96@gmail.com>
//
// This file is part of QTtt project.
// Licensed under the GPLv3.
// See the LICENSE file in the project root for more information.

#ifndef DIRECTIONS_H
#define DIRECTIONS_H

#include <QList>
#include <QSize>

class Directions {
public:
    enum class Direction {
        Horizontal,
        Vertical,
        BSlash,
        FSlash
    };

    static QSize getDirection(const Direction& direction);
    static QSize negative(const QSize& size);
    static QList<QSize> getList();
};

#endif // DIRECTIONS_H
