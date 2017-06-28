#include "../include/Computer.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

Computer::Computer() : Player(0, 5, "BattleShipAI")
{
    previousHit = false;
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

void Computer::generateAttack(int *xPtr, int *yPtr){
    bool correct = false;

    while(!correct){
        if (previousHit == true){ //generate attack based on recent hit on an enemies ship
            *xPtr = lastHit[0] + (rand() % 3 - 1); //last hit coords + random number between -1 and 1
            *yPtr = lastHit[1] + (rand() % 3 - 1); //last hit coords + random number between -1 and 1
        } else {
            *xPtr = rand() % 10 + 1; //plus 1 to compensate for header row
            *yPtr = rand() % 10 + 1; //plus 1 to compensate for header column
        }

        if (*xPtr <= 0 or *xPtr > 10){
          continue;
        } else if (*yPtr <= 0 or *yPtr > 10){
          continue;
        }
        cout<<*xPtr<<" "<<*yPtr<<endl;
        if (checkBoard(pBoard, *yPtr, *xPtr) == "o"){
            correct = true;
        }
    }

}

void Computer::attack(){
  int *x = new int;
  int *y = new int;
  generateAttack(x, y);

  string target = checkBoard(pBoard, *x, *y);
  if (target == "|" or target == "-"){
      previousHit = true;
      lastHit[0] = *x;
      lastHit[1] = *y;

      pBoard.changeBoard(*x, *y, "X"); //"X" is a hit
      rBoard.changeBoard(*x, *y, "X"); //"X" is a hit

      //getting the index of the ship that was hit
      int sIndex;
      for (int i = 0; i < 5; i++){
          if (ships[i].checkShip(*x, *y)){
              sIndex = i;
              break;
          }
      }
      ships[sIndex].hit(*x, *y); //takes out those ship coordinates
      if (!ships[sIndex].alive()){
          cout << name << " SANK your " << ships[sIndex].getName() << "!" << endl;
          shipCount--;
      }
      cout << name << " got a hit!" << endl;
  }
  else{
      previousHit = false;
      pBoard.changeBoard(*x, *y, "M"); //"M" is a miss
      rBoard.changeBoard(*x, *y, "M"); //"M" is a miss
      cout << name << " missed!" << endl;
  }
}

void Computer::printName(){
    cout << name;
}
