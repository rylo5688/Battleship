#include "Board.h"
#include <iostream>
#include <string>
#include <sstream>

Board::Board()
{
    board[0][0] = "\\";
    string temp = "ABCDEFGHIJ";

    //creating row and column labels
    for (int i = 1; i < 11; i++){
            board[0][i] = temp.substr(i-1, 1);
            stringstream ss;
            ss<<i-1;
            board[i][0] = ss.str();
    }

    //creating o for the rest of the spots
    for (int r = 1; r < 11; r++){
        for (int c = 1; c < 11; c++){
            board[r][c] = "o";
        }
    }
}

Board::Board(string b[11][11]){ //to be implemented for reading in a board
    for (int r = 0; r < 11; r++){
        for (int c = 0; c < 11; c++){
            board[r][c] = b[r][c];
        }
    }
}

Board::~Board()
{
    //dtor
}

void Board::printBoard(){
    for (int r = 0; r < 11; r++){
        for (int c = 0; c < 11; c++){
            cout<<board[r][c]<<" ";
        }
        cout<<endl;
    }
}

void Board::changeBoard(int c, int r, string change){
    board[r][c] = change;
}

string checkBoard(Board b, int r, int c){
    return b.board[r][c];
}
