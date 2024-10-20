#ifndef GAME_H
#define GAME_H



class Game
{
    static const int SIZE=3;
    char board[SIZE][SIZE]{{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    char game; //: ,X,O
public:

    int step;
    Game();
    void Change_game ();
    void Clear_board ();
    char Over ();
    bool Command (int x, int y);
    char Get_game();
    void Show_board ();

};

#endif // GAME_H
