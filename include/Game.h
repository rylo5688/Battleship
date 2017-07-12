#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Computer.h"
#include <iostream>

using namespace std;

class Game
{
public:
    Game(string fileName);
    virtual ~Game();
    void singlePlayerSetup();
    void singlePlayerRun();
    void multiPlayerSetup();
    void multiPlayerRun();
private:
    void printNewLine(int n);
    Player *player1;
    Player *player2;
    Computer *computer;
};

#endif // GAME_H
