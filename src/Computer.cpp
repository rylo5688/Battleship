#include "../include/Computer.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

Computer::Computer() : Player(0, 5, "BattleAI")
{

}

Computer::~Computer()
{
    //dtor
}

void Computer::createBoard(){ //computer creating its own board
    srand(time(NULL));
    int x;
    int y;

    for (int i = 0; i < 5; i++){
        int length = ships[i].getLength();
        string d = generateDirection();
        generateCoords(&x, &y);

        generatePlacement(d, &x, &y, length, i); //places the ship
    }
}

void Computer::generateCoords(int *xPtr, int *yPtr){ //generates coordinates
    bool correct = false;

    while (!correct){
        *xPtr = rand() % 10 + 1; //plus 1 to compensate for header row
        *yPtr = rand() % 10 + 1; //plus 1 to compensate for header column

        if (checkBoard(pBoard, *yPtr, *xPtr) == "o"){
            correct = true;
        }
    }
}

string Computer::generateDirection(){
    string directions = "udlr";

    return string(1, directions[rand()%4]);
}

void Computer::generatePlacement(string dir, int *xPtr, int *yPtr, int length, int sIndex){
    while(!checkPlacement(dir, xPtr, yPtr, length, sIndex)){ //goes until a spot is found
        generateCoords(xPtr, yPtr);
        generateDirection();
    }
}



void Computer::printName(){
    cout << name <<endl;
}
