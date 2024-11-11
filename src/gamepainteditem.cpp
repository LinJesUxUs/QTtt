#include "gamepainteditem.h"

#include "game.h"
#include <QPainter>

uint GamePaintedItem::m_sWidth = 3;
uint GamePaintedItem::m_sHeight = 3;
uint GamePaintedItem::m_sWinLength = 3;
uint GamePaintedItem::m_sFirstPlayer = 1;
uint GamePaintedItem::m_sPlayers = 2;

GamePaintedItem::GamePaintedItem() {
    if ( m_pGame == nullptr )
        m_pGame = new Game( QSize(m_sWidth, m_sHeight), m_sWinLength, m_sFirstPlayer, m_sPlayers );
    this->setMipmap(true);
    this->setAntialiasing(true);
    m_nPlayersPic.append(new QImage(QImage(":/images/y.jpg").scaled(getCellWidth(), getCellHeight() )) );
    m_nPlayersPic.append(new QImage(QImage(":/images/a.jpg").scaled(getCellWidth(), getCellHeight() )) );
    m_pGame->move(QSize(0,0),m_sFirstPlayer);
    m_pGame->move(QSize(2,2),m_sFirstPlayer+1);
}

GamePaintedItem::~GamePaintedItem()
{
    if ( m_pGame != nullptr )
        delete m_pGame;
    for ( int i = 0; i < m_nPlayersPic.size(); ++i )
        delete m_nPlayersPic[i];
}

void GamePaintedItem::paint(QPainter *painter)
{
    qreal cellWidth = getCellWidth();
    qreal cellHeight = getCellHeight();
    painter->save();
    painter->setBrush(QBrush(QImage(":/images/z.jpg").scaled(this->width(),this->height())));
    painter->drawRect(0,0,this->width(),this->height());
    drawCells(painter, cellWidth, cellHeight);
    drawGrid(painter, cellWidth, cellHeight);
    painter->restore();
}

void GamePaintedItem::drawGrid(QPainter *painter, const qreal &cellWidth, const qreal &cellHeight)
{
    painter->save();
    painter->setPen( QPen(Qt::gray,0) );
    for ( uint i = 1 ; i < m_pGame->getWidth(); ++i ) {
        painter->drawLine(cellWidth * i, 0,
                          cellWidth * i, this->height() );
    }
    for ( uint i = 1; i < m_pGame->getHeight(); ++i ) {
        painter->drawLine(0, cellHeight * i,
                          this->width(), cellHeight * i );
    }
    painter->restore();
}

void GamePaintedItem::drawCells(QPainter *painter, const qreal &cellWidth, const qreal &cellHeight)
{
    painter->save();
    for ( uint i = 0 ; i < m_pGame->getWidth(); ++i ) {
        for ( uint j = 0; j < m_pGame->getHeight(); ++j ) {
            if ( m_pGame->getField(i, j) > 0 ) {
                painter->setBrush(QBrush(*(m_nPlayersPic[ m_pGame->getField(i, j)-1 ]) ) );
                painter->drawRect(cellWidth * i, cellHeight * i,
                                  cellWidth, cellHeight);
            }
        }
    }
    painter->restore();
}

qreal GamePaintedItem::getCellWidth() const
{
    return this->width()/m_pGame->getWidth();
}

qreal GamePaintedItem::getCellHeight() const
{
    return this->height()/m_pGame->getHeight();
}

void GamePaintedItem::setWidth(const uint &newWidth)
{
    m_sWidth = newWidth;
}

void GamePaintedItem::setHeight(const uint &newHeight)
{
    m_sHeight = newHeight;
}

void GamePaintedItem::setWinLength(const uint &newWinLength)
{
    m_sWinLength = newWinLength;
}

void GamePaintedItem::setFirstPlayer(const uint &newFirstPlayer)
{
    m_sFirstPlayer = newFirstPlayer;
}

void GamePaintedItem::setPlayers(const uint &newPlayers)
{
    m_sPlayers = newPlayers;
}

uint &GamePaintedItem::getWidth()
{
    return m_sWidth;
}

uint &GamePaintedItem::getHeight()
{
    return m_sHeight;
}

uint &GamePaintedItem::getWinLength()
{
    return m_sWinLength;
}

uint &GamePaintedItem::getFirstPlayer()
{
    return m_sFirstPlayer;
}

uint &GamePaintedItem::getPlayers()
{
    return m_sPlayers;
}
