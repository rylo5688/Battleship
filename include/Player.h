#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include "Ship.h"
#include <iostream>

using namespace std;

class Player
{
    public:
        Player();
        Player (int i, int sC, string n);
        Player (string n);
        Player(Ship *s);
        virtual ~Player();
        void addShip(Ship s);
        void printShips();
        void printChoices(vector<Ship> s);
        void createBoard(); //when players will place their ships
        bool checkChoice(vector<Ship> s, string uIn, int *n); //checks if user input matches any of the ship choices
        bool checkCoords(string c, int *col, int *row); //x pointer then y pointer
        bool checkTarget(string c, int *col, int *row); //checks if inputed move is valid
        bool checkTarget(int *x, int *y);
        bool checkPlacement(string direction, int *col, int *row, int length, int sIndex);
        void printRBoard();
        void printPBoard();
        string checkMove(string n, int c, int r);
        int getShipCount();
        void printName();
        void clearScreen();
        string getName();
    protected:
        string name;
        int shipCount;
        Board pBoard; //players board where they place their ships
        Board rBoard; //revealed board to the other player that keeps track of their attacks
        int index;
        Ship ships[5];
    private:
};

#endif // PLAYER_H
