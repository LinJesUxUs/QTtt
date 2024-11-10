#include "gamepainteditem.h"

#include "game.h"
#include <QPainter>

GamePaintedItem::GamePaintedItem() {
    if ( game == nullptr )
        game = new Game( QSize(mWidth, mHeight), mWinLength, mFirstPlayer, mPlayers );
    this->setMipmap(true);
    this->setAntialiasing(true);
    nPlayersPic.append(new QImage(":/image/Y.jpg"));
    nPlayersPic.append(new QImage(":/image/A.jpg"));
}

GamePaintedItem::~GamePaintedItem()
{
    if ( game != nullptr )
        delete game;
}

void GamePaintedItem::paint(QPainter *painter)
{
    painter->save();
    painter->setBrush(QBrush(QImage(":/images/Z.jpg").scaled(this->width(),this->getHeight())));
    painter->drawRect(0,0,this->width(),this->getHeight());
    drawGrid(painter);
    painter->restore();
}

void GamePaintedItem::setWidth(uint &newWidth)
{
    mWidth = newWidth;
}

void GamePaintedItem::setHeight(uint &newHeight)
{
    mHeight = newHeight;
}

void GamePaintedItem::setWinLength(uint &newWinLength)
{
    mWinLength = newWinLength;
}

void GamePaintedItem::setFirstPlayer(uint &newFirstPlayer)
{
    mFirstPlayer = newFirstPlayer;
}

void GamePaintedItem::setPlayers(uint &newPlayers)
{
    mPlayers = newPlayers;
}

uint &GamePaintedItem::getWidth() const
{
    return mWidth;
}

uint &GamePaintedItem::getHeight() const
{
    return mHeight;
}

uint &GamePaintedItem::getWinLength() const
{
    return mWinLength;
}

uint &GamePaintedItem::getFirstPlayer() const
{
    return mFirstPlayer;
}

uint &GamePaintedItem::getPlayers() const
{
    return mPlayers;
}

void GamePaintedItem::drawGrid(QPainter *painter)
{
    painter->save();
    painter->setPen( QPen(Qt::gray,0) );
    for ( int i = 1 ; i < m_pGame->getWidth(); ++i ) {
        painter->drawLine(this->width()/m_pGame->getWidth() * i, 0,
                          this->width()/m_pGame->getWidth() * i, this->getHeight() );
    }
    for ( int i = 1; i < m_pGame->getHeight(); ++i ) {
        painter->drawLine(0, this->getHeight()/m_pGame->getHeight() * i,
                          this->width(), this->getHeight()/m_pGame->getHeight() * i );
    }
    painter->restore();
}

void GamePaintedItem::drawCells(QPainter *painter)
{

}
