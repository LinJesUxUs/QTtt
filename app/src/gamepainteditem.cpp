#include "gamepainteditem.h"
#include "settingsproxy.h"

#include <gamecore.h>
#include <QPainter>
#include <QBuffer>

SettingsProxy *GamePaintedItem::m_SpSettingsProxy = nullptr;

SettingsProxy *GamePaintedItem::getSpSettingsProxy()
{
    return m_SpSettingsProxy;
}

void GamePaintedItem::setSpSettingsProxy(SettingsProxy *newSpSettingsProxy)
{
    if ( m_SpSettingsProxy == nullptr)
        m_SpSettingsProxy = newSpSettingsProxy;
}

GamePaintedItem::GamePaintedItem() {
    if ( m_pGame == nullptr )
        m_pGame = new GameCore(QSize(m_SpSettingsProxy->getFieldWidth(),
                                     m_SpSettingsProxy->getFieldHeight()),
                               m_SpSettingsProxy->getWinLength(),
                               m_SpSettingsProxy->getFirstPlayer(),
                               m_SpSettingsProxy->getPlayersCount());

    this->setMipmap(true);
    this->setAntialiasing(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    m_nLocalPlayers.append(new QString("Game Over!"));
    for ( uint i = 1; i <= m_pGame->getNPlayers(); ++i ) {
        auto playerName = m_SpSettingsProxy->value("playersConf/" + QString::number(i) + "Name");
        if (playerName.isNull()) {
            m_SpSettingsProxy->setValue("playersConf/" + QString::number(i) + "Name", "Player" + QString::number(i) );
            m_SpSettingsProxy->getSpSettings()->sync();
            playerName = m_SpSettingsProxy->value("playersConf/" + QString::number(i) + "Name");
        }
        m_nLocalPlayers.append(new QString(playerName.toString()) );
    }

    m_nPlayersPic.append(new QImage(m_SpSettingsProxy->value("images/" + m_SpSettingsProxy->getPlayersConf("background")).value<QImage>()));
    m_nWinPlayersPic.append(new QImage(m_SpSettingsProxy->value("images/" + m_SpSettingsProxy->getPlayersConf("over")).value<QImage>()));

    for ( uint i = 1; i <= m_SpSettingsProxy->getPlayersCount(); ++i ) {
        m_nPlayersPic.append( new QImage(
            m_SpSettingsProxy->value("images/" + m_SpSettingsProxy->getPlayersConf(QString::number(i)+"Turn")).value<QImage>()
            ));
        m_nWinPlayersPic.append( new QImage(
            m_SpSettingsProxy->value("images/" + m_SpSettingsProxy->getPlayersConf(QString::number(i)+"Win")).value<QImage>()
            ));
    }

    connect(m_pGame,
            SIGNAL(onEnd(QSize,QSize,uint)),
            SLOT(onEnd(QSize,QSize,uint)));
    connect(m_pGame,
            SIGNAL(onMove(QSize,uint)),
            SLOT(onMove(QSize,uint)));
}

GamePaintedItem::~GamePaintedItem()
{
    if ( m_pEndValue != nullptr )
        delete m_pEndValue;
    if ( m_pGame != nullptr ) {
        disconnect(m_pGame,SIGNAL(onEnd(QSize,QSize,uint)),
                   this,SLOT(onEnd(QSize,QSize,uint)));
        disconnect(m_pGame,SIGNAL(onMove(QSize,uint)),
                   this,SLOT(onMove(QSize,uint)));
        delete m_pGame;
    }
    for ( int i = 0; i < m_nGameStatePic.size(); ++i ) {
        if (m_nGameStatePic[i] != nullptr) {
            delete m_nGameStatePic[i];
            m_nGameStatePic[i] = nullptr;
        }
    }
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
    m_SpSettingsProxy = nullptr;
}

void GamePaintedItem::restart()
{
    if (m_pGame != nullptr) {
        disconnect(m_pGame,SIGNAL(onEnd(QSize,QSize,uint)),
                   this,SLOT(onEnd(QSize,QSize,uint)));
        disconnect(m_pGame,SIGNAL(onMove(QSize,uint)),
                   this,SLOT(onMove(QSize,uint)));
        delete m_pGame;
        m_pGame = new GameCore(QSize(m_SpSettingsProxy->getFieldWidth(),
                                     m_SpSettingsProxy->getFieldHeight()),
                               m_SpSettingsProxy->getWinLength(),
                               m_SpSettingsProxy->getFirstPlayer(),
                               m_SpSettingsProxy->getPlayersCount());
        connect(m_pGame,
                SIGNAL(onEnd(QSize,QSize,uint)),
                SLOT(onEnd(QSize,QSize,uint)));
        connect(m_pGame,
                SIGNAL(onMove(QSize,uint)),
                SLOT(onMove(QSize,uint)));
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
        val = m_SpSettingsProxy->getPlayersConf(QString::number(m_pGame->turn()) + "Name" );
        val.append(" turn..");
    }
    else if (m_pEndValue->winPlayer > 0) {
        // val = m_SpSettingsProxy->getPlayersConf(QString::number(m_pEndValue->winPlayer) + "Name" );
        val = *m_nLocalPlayers[m_pEndValue->winPlayer];
        val.append(" WON!");
    }
    else
        val = *m_nLocalPlayers[m_pEndValue->winPlayer];
    return val;
}

uint GamePaintedItem::fieldWidth() {
    return m_SpSettingsProxy->getFieldWidth();
}

uint GamePaintedItem::fieldHeight() {
    return m_SpSettingsProxy->getFieldHeight();
}

void GamePaintedItem::mousePressEvent(QMouseEvent *event)
{
    m_mousePressPoint = QSize(event->position().rx() / getCellWidth(),
                               event->position().ry() / getCellHeight());
}

void GamePaintedItem::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_pEndValue != nullptr)
        return;
    if (m_nLocalPlayers[m_pGame->turn()] == nullptr)
        return;
    if (0 > event->position().rx()/getCellWidth() ||
        0 > event->position().ry()/getCellHeight())
        return;
    if (m_mousePressPoint == QSize(event->position().rx() / getCellWidth(),
                                   event->position().ry() / getCellHeight()) )
        m_pGame->move(m_mousePressPoint, m_pGame->turn());
}

void GamePaintedItem::paint(QPainter *painter)
{
    qreal cellWidth = getCellWidth();
    qreal cellHeight = getCellHeight();
    painter->save();
    painter->setBrush(QBrush(m_nPlayersPic[0]->scaled(this->width(),this->height())));
    painter->drawRect(0,0,this->width(),this->height());
    painter->restore();
    drawCells(painter, cellWidth, cellHeight);
    drawGrid(painter, cellWidth, cellHeight);
    drawEnd(painter);
}

void GamePaintedItem::onMove(const QSize &/*pos*/, const uint &/*player*/)
{
    emit gameStateChanged();
    update();
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
        uint minAspectRatio = qMin(this->width(),this->height());
        painter->save();
        painter->setPen(QPen(Qt::transparent,0));
        painter->setBrush(QBrush(
            m_nWinPlayersPic[ m_pEndValue->winPlayer ]->scaled(minAspectRatio, minAspectRatio)));
        painter->translate(this->width() > minAspectRatio ? (this->width() - minAspectRatio)/2 : 0 ,
                           this->height() > minAspectRatio ? (this->height() - minAspectRatio)/2 : 0);
        painter->drawRect(0, 0, minAspectRatio, minAspectRatio);
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
