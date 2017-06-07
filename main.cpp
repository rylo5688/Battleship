#include "include/Board.h"
#include "include/Ship.h"
#include "include/Player.h"
#include "include/Computer.h"
#include "include/PlayerInfo.h"

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

/*
Ryan Loi
TA: Camilla
10/27/16
*/

void initialize(string file, Player* one, Player* two, Computer* c){
  ifstream shipData;
  shipData.open(file);
  if(shipData.fail()){
      cout<<"something went wrong"<<endl;
  }
  else{
      string line;

      ///getting all the ship names and sizes from Ships.txt
      while(getline(shipData, line, '\n')){
          string word;
          stringstream ss;
          ss<<line;

          string name;
          int length;

          int index = 0;
          while(getline(ss, word, ',')){
              if (index == 0){ //ship's name
                  name = word;
              }
              else if(index == 1){ //ship's length
                  length = atoi(word.c_str());
              }
              index++;
          }
          Ship temp(name, length);

          one->addShip(temp);
          two->addShip(temp);
          c->addShip(temp);
      }
  }
}

int main()
{
    cout<<"Welcome to BattleShip!"<<endl;
    Player p1;
    Player p2;
    Computer computer;

    initialize("Ships.txt", &p1, &p2, &computer);

    computer.createBoard();
    computer.printPBoard();

    ///to ask if player wants to play
    string play;
    bool game;
    cout<<"Would you like to play(Y/N)? "<<endl;
    getline(cin, play);
    while (play != "y" and play != "Y" and play != "n" and play != "N"){
        cout<<endl;
        cout<<"---Invalid Input---"<<endl;
        cout<<"Would you like to play(Y/N)? "<<endl;
        getline(cin, play);
    }

    if (play == "y" or play == "Y"){
        game = true;
    }
    else if (play == "n" or play == "N"){
        game = false;
        cout<<"Boooooooooo"<<endl;
    }

    //Players creating their boards

    if (game){
        cout<<endl;
        cout<<"Player One's turn to place their ships!"<<endl;
        p1.createBoard();
        cout<<endl;
        p1.clearScreen();
        cout<<"Player Two's turn to place their ships!"<<endl;
        p2.createBoard();
        p1.clearScreen();
    }


    bool win = false;
    ///game begins here
    int turn = 1;
    while(game and !win){
        //5 line buffer
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;

        string pMove;
        if (turn%2==1){ //Player One's turn
            cout<<endl;
            cout<<"It's PLAYER ONE's turn"<<endl;

            cout<<endl;
            cout<<"  --ENEMIES BOARD--"<<endl;
            p2.printRBoard();
            cout<<"--------------------"<<endl;
            p1.printPBoard();
            cout<<"   --P1's BOARD--"<<endl;

            cout<<endl;
            cout<<"Enter a target(Ex. A3): "<<endl;
            getline(cin, pMove);
            int x;
            int *xPointer = &x;
            int y;
            int *yPointer = &y;

            //attacking the other player
            while(!p2.checkTarget(pMove, xPointer, yPointer)){
                cout<<endl;
                cout<<" ---Invalid Target---"<<endl;
                cout<<"Enter a target(Ex. A3): "<<endl;
                getline(cin, pMove);
            }
            //they have a valid target
            cout<<p2.checkMove(x, y)<<endl;
            if (p2.getShipCount() == 0){ //that means player one has won
                win = true;
            }
        }

        else if(turn%2==0){ //Player Two's turn
            cout<<endl;
            cout<<"It's PLAYER TWO's turn"<<endl;

            cout<<endl;
            cout<<"  --ENEMIES BOARD--"<<endl;
            p1.printRBoard();
            cout<<"--------------------"<<endl;
            p2.printPBoard();
            cout<<"   --P2's BOARD--"<<endl;

            cout<<endl;
            cout<<"Enter a target(Ex. A3): "<<endl;
            getline(cin, pMove);
            int x;
            int *xPointer = &x;
            int y;
            int *yPointer = &y;

            //attacking the other player
            while(!p1.checkTarget(pMove, xPointer, yPointer)){
                cout<<endl;
                cout<<" ---Invalid Target---"<<endl;
                cout<<"Enter a target(Ex. A3): "<<endl;
                getline(cin, pMove);
            }
            //they have a valid target
            cout<<p1.checkMove(x, y)<<endl;
            if (p1.getShipCount() == 0){ //that means player two has won
                win = true;
            }

        }

        string moveOn;
        cout<<"Enter 'Y' to move onto the next turn: "<<endl;
        getline(cin, moveOn);
        while (moveOn != "Y" and !win){
            cout<<"Enter 'Y' to move onto the next turn: "<<endl;
            getline(cin, moveOn);
        }

        //5 line buffer
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;

        if (!win){
            turn++;
        }
    }
    //somebody has won!
    if (turn%2==1){ //Player 1 has won
        cout<<"Player One has won the game! "<<endl;
        cout<<"Would you like to enter a name to add to the list of winners(Y/N): "<<endl;
        string answer;
        getline(cin, answer);
        while (answer != "Y" and answer != "y" and answer != "N" and answer != "n"){
            cout<<"Would you like to enter a name to add to the list of winners(Y/N): "<<endl;
            getline(cin, answer);
        }
        if (answer == "y" or answer == "Y"){
            string name;
            cout<<"Enter your name: "<<endl;
            getline(cin, name);
            ofstream winners("winners.txt", ios::app);
            winners<<name;
            winners.close();
            cout<<"Thanks for playing!"<<endl;
        }
        else{
            cout<<"Thanks for playing!"<<endl;
        }
    }
    else if (turn%2==0){ //Player 2 has won the game
        cout<<"Player Two has won the game! "<<endl;
        cout<<"Would you like to enter a name to add to the list of winners(Y/N): "<<endl;
        string answer;
        getline(cin, answer);
        while (answer != "Y" and answer != "y" and answer != "N" and answer != "n"){
            cout<<"Would you like to enter a name to add to the list of winners(Y/N): "<<endl;
            getline(cin, answer);
        }
        if (answer == "y" or answer == "Y"){
            string name;
            cout<<"Enter your name: "<<endl;
            getline(cin, name);
            ofstream winners("winners.txt", ios::app);
            winners<<name;
            winners.close();
            cout<<"Thanks for playing!"<<endl;
        }
        else{
            cout<<"Thanks for playing!"<<endl;
        }
    }

    return 0;
}
