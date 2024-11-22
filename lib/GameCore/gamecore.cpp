#include "gamecore.h"

#include <directions.h>
#include <QSize>

GameCore::GameCore(const QSize &field, const uint &winLength, const uint &firstPlayer, const uint &players, QObject *parent)
    : QObject(parent)
{
    m_nField.resize(field.width() < 1 ? 1 : field.width() );
    for( int i = 0; i < m_nField.size(); ++i )
        m_nField[i].resize(field.height() < 1 ? 1 : field.height() );

    mWinLength = qMin(
        int(int(winLength) < 1 ? 1 : winLength),
        (int)qMin(m_nField.size(), m_nField[0].size()));

    mPlayers = (int(players) < 0) ? 0 : players;
    mTurn = firstPlayer > mPlayers ? mPlayers : firstPlayer;
}

void GameCore::isEnd(const QSize &pos) const
{
    QSize begin;
    QSize end;
    QList<QSize> lst( Directions::getList() );
    for ( int i = 0; i < lst.size(); ++i ) {
        begin = vecLen(pos,Directions::negative(lst[i]));
        end = vecLen(pos,lst[i]);
        if ( isWinRange(begin, end) ) {
            emit onEnd( begin, end, getField(pos) );
            return;
        }
    }
}

bool GameCore::isWinRange(const QSize &begin, const QSize &end) const
{
    if ( begin.width() == end.width() )
        return ( mWinLength == (uint)(end.height() - begin.height() + 1) );
    return ( mWinLength == (uint)(begin.width() > end.width() ?
                                  begin.width() - end.width() :
                                  end.width() - begin.width())+ 1 );
}

const QSize GameCore::vecLen(const QSize &pos, const QSize &offset) const
{
    QSize val = pos;
    try {
        uint fPos = getField(pos);
        do {
            val.rwidth()+=offset.width();
            val.rheight()+=offset.height();
        }
        while ( fPos == getField(val) );
    }
    catch ( const char* err_msg) {}
    val.rwidth()-=offset.width();
    val.rheight()-=offset.height();
    if( isOutOfRange(val) ) {
        val.rwidth()+=offset.width();
        val.rheight()+=offset.height();
    }
    return val;
}

const QSize GameCore::vecLen(const QSize &pos, const int xOffset, const int yOffset) const
{
    QSize val = pos;
    try {
        uint fPos = getField(pos);
        do {
            val.rwidth()+=xOffset;
            val.rheight()+=yOffset;
        }
        while ( fPos == getField(val) );
    }
    catch ( const char* err_msg) {}
    val.rwidth()-=xOffset;
    val.rheight()-=yOffset;
    if( isOutOfRange(val) ) {
        val.rwidth()+=xOffset;
        val.rheight()+=yOffset;
    }
    return val;
}

bool GameCore::isBusy(const QSize &pos) const
{
    return getField(pos);
}

bool GameCore::isOutOfRange(const QSize &pos) const
{
    if ( pos.isValid() )
        return isOutOfRange( pos.width(), pos.height() );
    return true;
}

bool GameCore::isOutOfRange(const uint w, const uint h) const
{
    return ( w >= m_nField.size() || h >= m_nField[0].size() );
}

void GameCore::nextTurn()
{
    if ( mTurn+1 > mPlayers )
        mTurn = 1;
    else
        mTurn++;
}

const uint &GameCore::getWinLength() const
{
    return mWinLength;
}

const uint &GameCore::getNPlayers() const
{
    return mPlayers;
}

uint GameCore::getWidth() const
{
    return m_nField.size();
}

uint GameCore::getHeight() const
{
    return m_nField[0].size();
}

uint GameCore::getField(const QSize &pos) const
{
    if ( isOutOfRange(pos) ) {
        throw "Out of range!";
        return 0;
    }
    return m_nField[pos.width()][pos.height()];
}

uint GameCore::getField(const uint w, const uint h) const
{
    if ( isOutOfRange( w, h ) ) {
        throw "Out of range!";
        return 0;
    }
    return m_nField[w][h];
}

void GameCore::move(const QSize &pos, const uint &player)
{
    try {
        if ( !isBusy(pos) ) {
            if ( player == mTurn ) {
                m_nField[pos.width()][pos.height()] = player;
                emit onMove(pos,player);
                isEnd(pos);
                nextTurn();
                return;
            }
        }
        emit onNoMove(pos,player);
    }
    catch (const char* err_msg) {
        emit onNoMove(pos,player);
    }
}

uint GameCore::turn() const
{
    return mTurn;
}
