/*
Ryan Loi
Console Battleship
*/

#include "include/Board.h"
#include "include/Ship.h"
#include "include/Player.h"
#include "include/Computer.h"
#include "include/Game.h"

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

bool playDecision(){
    string play;

    cout<<"Would you like to play(Y/N)? "<<endl;
    getline(cin, play);
    while (play != "y" and play != "Y" and play != "n" and play != "N"){
        cout<<endl;
        cout<<"---Invalid Input---"<<endl;
        cout<<"Would you like to play(Y/N)? "<<endl;
        getline(cin, play);
    }

    if (play == "y" or play == "Y"){
        return true;
    }
    else if (play == "n" or play == "N"){
        cout<<"Boooooooooo"<<endl;
        return false;
    }
}

int gameTypeDecision(){
    int decision;

    cout << "Do you want to play Single Player(1) or Multiplayer(2)" << endl;
    cin >> decision;
    while (decision != 1 and decision != 2){
        cout<<endl;
        cout << "---Invalid Input---" << endl;
        cout << "Do you want to play Single Player(1) or Multiplayer(2)" << endl;
        cin >> decision;
    }

    cin.ignore();
    cin.clear();
    return decision;
}

int main(int argc, char* argv[])
{
    if (argc > 2){
        cout << "Incorrect starting information for startup!" << endl;
        return 0;
    }

    string fileName = argv[1];
    cout<<"Welcome to BattleShip!"<<endl;

    //Askes if player wants to play
    bool game = playDecision(); //true if player wants to play and false otherwise

    //Players creating their boards
    if (game){
        Game *GameController = new Game(fileName);
        int gameType = gameTypeDecision();

        if (gameType == 1){ //Single player
            GameController->singlePlayerSetup();
            GameController->singlePlayerRun();
        } else { //Multiplayer
            GameController->multiPlayerSetup();
            GameController->multiPlayerRun();
        }
    }

    return 0;
}
