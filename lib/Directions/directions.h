#ifndef DIRECTIONS_H
#define DIRECTIONS_H

#include <QSize>
#include <QList>

class Directions
{
public:
    enum class Direction {
        Horizontal,
        Vertical,
        BSlash,
        FSlash
    };

    static QSize getDirection(const Direction &direction);
    static QSize negative(const QSize &size);
    static QList<QSize> getList();
};

#endif // DIRECTIONS_H
