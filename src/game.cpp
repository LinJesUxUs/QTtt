#include "game.h"

Game::Game()
{
    Clear_board();

}
void Game::Change_game (){
    switch (game)
    {
    case 'O':
    game='X';
        break;
    case 'X':
    game='O';
        break;
    }
}

void Game::Clear_board (){
    for (int i=0;i<SIZE;++i){
        for (int j=0;j<SIZE;++j){
        board[i][j]=' ';
    }
    }
    game='X';
    step=0;
}

char Game::Over (){
    if (board[0][0]=='X'||board[0][0]=='O'){
        if (board[0][0]==board[0][1]&&board[0][1]==board[0][2])
        {return board[0][0];}
        if (board[0][0]==board[1][0]&&board[1][0]==board[2][0])
        {return board[0][0];}
        if (board[0][0]==board[1][1]&&board[1][1]==board[2][2])
        {return board[0][0];}
    }
    if (board[1][1]=='X'||board[1][1]=='O'){
        if (board[1][0]==board[1][1]&&board[1][1]==board[1][2])
        {return board[1][1];}
        if (board[0][1]==board[1][1]&&board[1][1]==board[2][1])
        {return board[1][1];}
        if (board[0][2]==board[1][1]&&board[1][1]==board[2][0])
        {return board[1][1];}
    }
    if (board[2][2]=='X'||board[2][2]=='O'){
        if (board[0][2]==board[1][2]&&board[1][2]==board[2][2])
        {return board[2][2];}
        if (board[2][0]==board[2][1]&&board[2][1]==board[2][2])
        {return board[2][2];}
    }
    return ' ';
}

char Game::Get_game(){
    return game;
}

bool Game::Command (int x, int y) {
    if ((0<=x)&&(x<SIZE)&&(0<=y)&&(y<SIZE)&&(board[x][y]==' ')) {
        board[x][y]=game;
        ++step;
        return true;
    }
    else { return false;}
}
