#include "gamepainteditem.h"

#include <gamecore.h>
#include <QPainter>

uint GamePaintedItem::m_sWidth = 3;
uint GamePaintedItem::m_sHeight = 3;
uint GamePaintedItem::m_sWinLength = 3;
uint GamePaintedItem::m_sFirstPlayer = 1;
uint GamePaintedItem::m_sPlayers = 2;

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

GamePaintedItem::GamePaintedItem() {
    if ( m_pGame == nullptr )
        m_pGame = new GameCore( QSize(m_sWidth, m_sHeight), m_sWinLength, m_sFirstPlayer, m_sPlayers );
    this->setMipmap(true);
    this->setAntialiasing(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    m_nLocalPlayers.append(new QString("Game Over!"));
    for ( uint i = 1; i <= m_sPlayers; ++i ) {
        m_nLocalPlayers.append(new QString("Player") );
        m_nLocalPlayers.last()->append(QString::number(i));
        qDebug() << *m_nLocalPlayers.last() << " added.";
    }
    m_nPlayersPic.append(new QImage(":/images/z.jpg") );
    m_nPlayersPic.append(new QImage(":/images/y.jpg") );
    m_nPlayersPic.append(new QImage(":/images/a.jpg") );
    m_nWinPlayersPic.append(new QImage(":/images/over.jpg") );
    m_nWinPlayersPic.append(new QImage(":/images/ywin.jpg") );
    m_nWinPlayersPic.append(new QImage(":/images/awin.jpg") );
    connect(m_pGame,SIGNAL(onEnd(QSize,QSize,uint)),SLOT(onEnd(QSize,QSize,uint)));
    connect(m_pGame,SIGNAL(onMove(QSize,uint)),SLOT(onMove(QSize,uint)));
}

GamePaintedItem::~GamePaintedItem()
{
    if ( m_pEndValue != nullptr )
        delete m_pEndValue;
    if ( m_pGame != nullptr )
        delete m_pGame;
    for ( int i = 0; i < m_nPlayersPic.size(); ++i )
        delete m_nPlayersPic[i];
    for ( int i = 0; i < m_nWinPlayersPic.size(); ++i )
        delete m_nWinPlayersPic[i];
    for ( int i = 0; i < m_nLocalPlayers.size(); ++i ) {
        if (m_nLocalPlayers[i] != nullptr) {
            delete m_nLocalPlayers[i];
            m_nLocalPlayers[i] = nullptr;
        }
    }
}

void GamePaintedItem::restart()
{
    qDebug() << "restart called!!!";
    if (m_pGame != nullptr) {
        disconnect(m_pGame,SIGNAL(onEnd(QSize,QSize,uint)),this,SLOT(onEnd(QSize,QSize,uint)));
        disconnect(m_pGame,SIGNAL(onMove(QSize,uint)),this,SLOT(onMove(QSize,uint)));
        delete m_pGame;
        m_pGame = new GameCore( QSize(m_sWidth, m_sHeight), m_sWinLength, m_sFirstPlayer, m_sPlayers );
        connect(m_pGame,SIGNAL(onEnd(QSize,QSize,uint)),SLOT(onEnd(QSize,QSize,uint)));
        connect(m_pGame,SIGNAL(onMove(QSize,uint)),SLOT(onMove(QSize,uint)));
    }
    if (m_pEndValue != nullptr) {
        delete m_pEndValue;
        m_pEndValue = nullptr;
    }
    emit gameStateChanged();
    update();
}

QString GamePaintedItem::gameState()
{
    QString val;
    if (m_pEndValue == nullptr ) {
        val = *m_nLocalPlayers[m_pGame->turn()];
        val.append("'s move..");
    }
    else if (m_pEndValue->winPlayer > 0) {
        val = *m_nLocalPlayers[m_pEndValue->winPlayer];
        val.append(" WON!");
    }
    else
        val = *m_nLocalPlayers[m_pEndValue->winPlayer];
    return val;
}

QVariant GamePaintedItem::gameStateImage()
{
    if (m_pEndValue != nullptr) {
        if (m_pEndValue->winPlayer == 0)
            return *m_nPlayersPic[m_pGame->turn()];
    }
    return *m_nPlayersPic[m_pGame->turn()];
}

void GamePaintedItem::mousePressEvent(QMouseEvent *event)
{
    if (m_pEndValue == nullptr && m_nLocalPlayers[m_pGame->turn()] != nullptr)
        m_pGame->move(QSize(event->position().rx()/getCellWidth(), event->position().ry()/getCellHeight()), m_pGame->turn());
}

void GamePaintedItem::paint(QPainter *painter)
{
    qreal cellWidth = getCellWidth();
    qreal cellHeight = getCellHeight();
    painter->save();
    painter->setBrush(QBrush(m_nPlayersPic[0]->scaled(this->width(),this->height())));
    painter->drawRect(0,0,this->width(),this->height());
    drawCells(painter, cellWidth, cellHeight);
    drawGrid(painter, cellWidth, cellHeight);
    drawEnd(painter);
    painter->restore();
}

void GamePaintedItem::onMove(const QSize &pos, const uint &player)
{
    emit gameStateChanged();
    update();
    if (pos==pos&&player==player){} // plug down
}

void GamePaintedItem::onEnd(const QSize &posBegin, const QSize &posEnd, const uint &player)
{
    if (m_pEndValue==nullptr) {
        m_pEndValue = new EndValue{posBegin, posEnd, player};
        emit gameStateChanged();
        update();
    }
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
                painter->setBrush(QBrush(m_nPlayersPic[ m_pGame->getField(i, j) ]->scaled(cellWidth, cellHeight)) );
                painter->drawRect(cellWidth * i, cellHeight * j,
                                  cellWidth, cellHeight);
            }
        }
    }
    painter->restore();
}

void GamePaintedItem::drawEnd(QPainter *painter)
{
    if (m_pEndValue != nullptr) {
        painter->save();
        painter->setBrush(QBrush(m_nWinPlayersPic[ m_pEndValue->winPlayer ]->scaled(this->width(), this->height())) );
        painter->drawRect(0, 0, this->width(), this->height());
        painter->restore();
    }
}

qreal GamePaintedItem::getCellWidth() const
{
    return this->width()/m_pGame->getWidth();
}

qreal GamePaintedItem::getCellHeight() const
{
    return this->height()/m_pGame->getHeight();
}
