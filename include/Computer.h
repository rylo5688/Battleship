#ifndef COMPUTER_H
#define COMPUTER_H
#include "Player.h"
#include <iostream>

using namespace std;

class Computer: public Player
{
    public:
        Computer();
        virtual ~Computer();
        void createBoard();
        void printName();
        void generateCoords(int *x, int *y);
        string generateDirection();
        void generatePlacement(string dir, int *xPtr, int *yPtr, int length, int sIndex);
    protected:
    private:
};

#endif // COMPUTER_H
