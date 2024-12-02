#include "gamepainteditem.h"

#include <gamecore.h>
#include <QPainter>
#include <QBuffer>
#include <QSettings>

GamePaintedItem::GamePaintedItem() {
    QCoreApplication::setApplicationName("LinJesUxUs");
    QCoreApplication::setOrganizationName("QTtt");
    if ( settings == nullptr )
        settings = new QSettings();
    settings->beginGroup("GameConfig");
    if ( m_pGame == nullptr )
        m_pGame = new GameCore(settings->value("fieldQSize").toSize(),
                               settings->value("WinLength").toUInt(),
                               settings->value("FirstPlayer").toUInt(),
                               settings->value("PlayersCount").toUInt());
    qDebug() << settings->value("fieldQSize").toSize();
    qDebug() << settings->value("WinLength").toUInt();
    qDebug() << settings->value("PlayersCount").toUInt();
    qDebug() << settings->value("FirstPlayer").toUInt();
    settings->endGroup();
    this->setMipmap(true);
    this->setAntialiasing(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    m_nLocalPlayers.append(new QString("Game Over!"));
    for ( uint i = 1; i <= m_pGame->getNPlayers(); ++i ) {
        m_nLocalPlayers.append(new QString("Player") );
        m_nLocalPlayers.last()->append(QString::number(i));
        qDebug() << *m_nLocalPlayers.last() << " added.";
    }
    settings->beginGroup("images");
    m_nPlayersPic.append(new QImage(settings->value("z").value<QImage>()));
    m_nPlayersPic.append(new QImage(settings->value("y").value<QImage>()));
    m_nPlayersPic.append(new QImage(settings->value("a").value<QImage>()));
    m_nWinPlayersPic.append(new QImage(settings->value("over").value<QImage>()));
    m_nWinPlayersPic.append(new QImage(settings->value("ywin").value<QImage>()));
    m_nWinPlayersPic.append(new QImage(settings->value("awin").value<QImage>()));
    settings->endGroup();
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    for (auto i: std::as_const(m_nPlayersPic) ) {
        i->save(&buffer);
        m_nGameStatePic.append(new QUrl("data:image/jpg;base64," + QString::fromUtf8(byteArray.toBase64())));
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
    if (settings != nullptr)
        delete settings;
    if ( m_pEndValue != nullptr )
        delete m_pEndValue;
    if ( m_pGame != nullptr )
        delete m_pGame;
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
}

void GamePaintedItem::restart()
{
    qDebug() << "restart called!!!";
    if (m_pGame != nullptr) {
        disconnect(m_pGame,SIGNAL(onEnd(QSize,QSize,uint)),
                   this,SLOT(onEnd(QSize,QSize,uint)));
        disconnect(m_pGame,SIGNAL(onMove(QSize,uint)),
                   this,SLOT(onMove(QSize,uint)));
        delete m_pGame;
        settings->beginGroup("GameConfig");
        m_pGame = new GameCore(settings->value("fieldQSize").toSize(),
                               settings->value("WinLength").toUInt(),
                               settings->value("FirstPlayer").toUInt(),
                               settings->value("PlayersCount").toUInt());
        settings->endGroup();
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

QUrl GamePaintedItem::gameStateImage()
{
    if (m_pEndValue != nullptr)
        return *m_nGameStatePic[m_pEndValue->winPlayer];
    return *m_nGameStatePic[m_pGame->turn()];
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
