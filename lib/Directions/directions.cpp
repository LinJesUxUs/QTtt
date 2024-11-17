#include "directions.h"

QSize Directions::getDirection(const Direction &direction)
{
    switch (direction) {
    case Direction::Horizontal: return QSize(1,0);
    case Direction::Vertical: return QSize(0,1);
    case Direction::BSlash: return QSize(1,1);
    case Direction::FSlash: return QSize(-1,1);
    }
    return QSize(0,0);
}

QSize Directions::negative(const QSize &size)
{
    return QSize(0,0)-size;
}

QList<QSize> Directions::getList()
{
    QList<QSize> directionsList;
    directionsList.append(getDirection(Direction::Horizontal));
    directionsList.append(getDirection(Direction::Vertical));
    directionsList.append(getDirection(Direction::BSlash));
    directionsList.append(getDirection(Direction::FSlash));
    return directionsList;
}
