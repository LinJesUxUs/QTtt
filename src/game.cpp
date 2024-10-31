#include "game.h"

#include <QSize>

const bool Game::isBusy(const QSize &pos) const
{
    return getField(pos);
}

const bool Game::isOutOfRange(const QSize &pos) const
{
    if ( pos.isValid() )
        return isOutOfRange( pos.width(), pos.height() );
    return false;
}

const bool Game::isOutOfRange(const uint w, const uint h) const
{
    return ( w >= m_nField.size() || h >= m_nField[0].size() );
}

const bool Game::isWinRange(const QSize &begin, const QSize &end) const
{
    if ( begin.width() == end.width() )
        return ( nWinLength == end.height() - begin.height() + 1 );
    return ( nWinLength == end.width() - begin.width() + 1 );
}

void Game::isEnd(const QSize &pos) const
{
    if( isBusy(pos) ){
        if ( isWinRange( vecLen(pos,-1,0), vecLen(pos,1,0) ) )
            emit onEnd( vecLen(pos,-1,0), vecLen(pos,1,0), getField(pos) );
        else if ( isWinRange( vecLen(pos,0,-1), vecLen(pos,0,1) ) )
            emit onEnd( vecLen(pos,0,-1), vecLen(pos,0,1), getField(pos) );
        else if ( isWinRange( vecLen(pos,-1,1), vecLen(pos,1,-1) ) )
            emit onEnd( vecLen(pos,-1,1), vecLen(pos,1,-1), getField(pos) );
        else if ( isWinRange( vecLen(pos,-1,-1), vecLen(pos,1,1) ) )
            emit onEnd( vecLen(pos,-1,-1), vecLen(pos,1,1), getField(pos) );
    }
}

void Game::nextTurn()
{
    if ( nTurn+1 > nPlayers )
        nTurn = 1;
    else
        nTurn++;
}

const QSize &Game::vecLen(const QSize &pos, const int xOff, const int yOff) const
{
    QSize val = pos;
    try {
        uint fPos = getField(pos);
        do {
            val.rwidth()+=xOff;
            val.rheight()+=yOff;
        }
        while ( fPos == getField(val) );
    }
    catch ( const char* err_msg) {}
    val.rwidth()-=xOff;
    val.rheight()-=yOff;
    if( isOutOfRange(val) ) {
        val.rwidth()+=xOff;
        val.rheight()+=yOff;
    }
    return val;
}

Game::Game(const QSize &field, const uint &winLength, const uint players, QObject *parent)
    : QObject(parent), nWinLength(winLength), nPlayers(players), nTurn(1)
{
    m_nField.resize(field.width());
    for( auto i: m_nField ) {
        i.resize(field.height());
        for( auto j: i ) {
            j = 0;
        }
    }
}

const uint &Game::getField(const QSize &pos) const
{
    if ( isOutOfRange(pos) ) {
        throw "Out of range!";
        return 0;
    }
    return m_nField[pos.width()][pos.height()];
}

const uint &Game::getField(const uint w, const uint h) const
{
    if ( isOutOfRange( w, h ) ) {
        throw "Out of range!";
        return 0;
    }
    return m_nField[w][h];
}

const uint &Game::getNWinLength() const
{
    return nWin;
}

const uint &Game::getNPlayers() const
{
    return nPlayers;
}

void Game::move(const QSize &pos, const uint &player)
{
    if ( !isBusy(pos) ) {
        if ( player == nTurn ) {
            m_nField[pos.width()][pos.height()] = player;
            emit onMove(pos,player);
            isEnd(pos);
            nextTurn();
        }
    }
}
