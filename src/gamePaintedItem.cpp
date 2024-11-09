#include "gamePaintedItem.h"

#include "game.h"
#include <QPainter>

GamePaintedItem::GamePaintedItem() {
    if ( game == nullptr )
        game = new Game(QSize(WIDTH, HEIGHT));
    this->setMipmap(true);
    this->setAntialiasing(true);
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
    for ( int i = 1 ; i < WIDTH; ++i ) {
        painter->drawLine( this->width()/WIDTH * i, 0, this->width()/WIDTH * i, this->height() );
    }
    for ( int i = 1; i < HEIGHT; ++i ) {
        painter->drawLine( 0, this->height()/HEIGHT * i, this->width(), this->height()/HEIGHT * i );
    }
    painter->restore();
}

