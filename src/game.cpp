#include "game.h"

#include <QSize>

Game::Game(const QSize &field, const uint &winLength, const uint firstPlayer, const uint players, QObject *parent)
    : QObject(parent), WIN_LENGTH(winLength), PLAYERS(players), mTurn( firstPlayer > players ? players : firstPlayer )
{
    m_nField.resize(field.width());
    for( auto i: qAsConst(m_nField) ) {
        i.resize(field.height(),0);
    }
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

bool Game::isWinRange(const QSize &begin, const QSize &end) const
{
    if ( begin.width() == end.width() )
        return ( WIN_LENGTH == (uint)(end.height() - begin.height() + 1) );
    return ( WIN_LENGTH == (uint)(end.width() - begin.width() + 1) );
}

const QSize Game::vecLen(const QSize &pos, const int xOff, const int yOff) const
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

bool Game::isBusy(const QSize &pos) const
{
    return getField(pos);
}

bool Game::isOutOfRange(const QSize &pos) const
{
    if ( pos.isValid() )
        return isOutOfRange( pos.width(), pos.height() );
    return false;
}

bool Game::isOutOfRange(const uint w, const uint h) const
{
    return ( w >= m_nField.size() || h >= m_nField[0].size() );
}

void Game::nextTurn()
{
    if ( mTurn+1 > PLAYERS )
        mTurn = 1;
    else
        mTurn++;
}

const uint &Game::getNWinLength() const
{
    return WIN_LENGTH;
}

const uint &Game::getNPlayers() const
{
    return PLAYERS;
}

const uint &Game::getWidth() const
{
    return m_nField.size();
}

const uint &Game::getHeight() const
{
    return m_nField[0].size();
}

uint Game::getField(const QSize &pos) const
{
    if ( isOutOfRange(pos) ) {
        throw "Out of range!";
        return 0;
    }
    return m_nField[pos.width()][pos.height()];
}

uint Game::getField(const uint w, const uint h) const
{
    if ( isOutOfRange( w, h ) ) {
        throw "Out of range!";
        return 0;
    }
    return m_nField[w][h];
}

void Game::move(const QSize &pos, const uint &player)
{
    if ( !isBusy(pos) ) {
        if ( player == mTurn ) {
            m_nField[pos.width()][pos.height()] = player;
            emit onMove(pos,player);
            isEnd(pos);
            nextTurn();
        }
    }
}
