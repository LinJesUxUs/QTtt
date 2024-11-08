#include "gamePaintedItem.h"

#include "game.h"
#include <QPainter>

GamePaintedItem::GamePaintedItem() {
    if ( game == nullptr )
        game = new Game(QSize(3,3));
}

GamePaintedItem::~GamePaintedItem()
{
    if ( game != nullptr )
        delete game;
}

void GamePaintedItem::paint(QPainter *painter)
{
    painter->save();
    painter->setBrush(QBrush(QImage(":/images/Z.jpg").scaled(this->width(),this->height())));
    painter->drawRect(0,0,this->width(),this->height());
    drawGrid(painter);
    painter->restore();
}

void GamePaintedItem::drawGrid(QPainter *painter)
{
    painter->save();
    painter->setPen( QPen(Qt::gray,0) );
    painter->drawLine( 0, this->height()/3, this->width(), this->height()/3 );
    painter->drawLine( 0, this->height()/1.5, this->width(), this->height()/1.5 );
    painter->drawLine( this->width()/3, 0, this->width()/3, this->height() );
    painter->drawLine( this->width()/1.5, 0, this->width()/1.5, this->height() );
    painter->restore();
}
