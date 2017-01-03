#ifndef COMPUTER_H
#define COMPUTER_H
#include "Player.h"
#include <iostream>

using namespace std;

class Computer: public Player
{
    public:
        Computer(string);
        virtual ~Computer();
        void createBoard();
        void printName();
    protected:
    private:
        string level;
};

#endif // COMPUTER_H
