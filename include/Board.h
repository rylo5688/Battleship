#ifndef BOARD_H
#define BOARD_H

#include <iostream>

using namespace std;

class Board
{
    public:
        Board();
        Board(string[11][11]); //used for when a board is imported
        virtual ~Board();
        void printBoard();
        void changeBoard(int c, int r, string change);
    protected:
        friend string checkBoard(Board b, int r, int c);
    private:
        string board[11][11];

};

#endif // BOARD_H
