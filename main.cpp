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

//Function for printing x number of new lines
void printNewLine(int x){
  for (int i = 0; i < x; i++){
    cout<<endl;
  }
}

void singlePlayerRun(Player *p1, Computer *computer){
  bool win = false;

  string pMove;
  while(!win){
    printNewLine(6);
    cout<<"It's PLAYER ONE's turn"<<endl;
    cout<<endl;

    cout<<"  --ENEMIES BOARD--"<<endl;
    computer->printRBoard();
    cout<<"--------------------"<<endl;
    p1->printPBoard();
    cout<<"   --P1's BOARD--"<<endl;

    cout<<endl;
    cout<<"Enter a target(Ex. A3): "<<endl;

    getline(cin, pMove);
    int *x = new int;
    int *y = new int;

    //attacking the other player
    while(!computer->checkTarget(pMove, x, y)){
        cout<<endl;
        cout<<" ---Invalid Target---"<<endl;
        cout<<"Enter a target(Ex. A3): "<<endl;
        getline(cin, pMove);
    }
    //User has selected a valid target
    cout<<computer->checkMove(p1->getName(), *x, *y)<<endl;

    if (computer->getShipCount() == 0){ //that means player one has won
        win = true;
    }

    //Computer attack logic 
    printNewLine(3);
    computer->attack(p1);
    printNewLine(3);
  }
}

void multiPlayerRun(Player *p1, Player *p2){
  bool win = false;
  ///game begins here
  int turn = 1;
  while(!win){
      printNewLine(5);

      string pMove;
      if (turn%2==1){ //Player One's turn
          cout<<endl;
          cout<<"It's PLAYER ONE's turn"<<endl;

          cout<<endl;
          cout<<"  --ENEMIES BOARD--"<<endl;
          p2->printRBoard();
          cout<<"--------------------"<<endl;
          p1->printPBoard();
          cout<<"   --P1's BOARD--"<<endl;

          cout<<endl;
          cout<<"Enter a target(Ex. A3): "<<endl;
          getline(cin, pMove);
          int *x = new int;
          int *y = new int;

          //attacking the other player
          while(!p2->checkTarget(pMove, x, y)){
              cout<<endl;
              cout<<" ---Invalid Target---"<<endl;
              cout<<"Enter a target(Ex. A3): "<<endl;
              getline(cin, pMove);
          }

          //they have a valid target
          cout<<p2->checkMove(p1->getName(), *x, *y)<<endl;
          if (p2->getShipCount() == 0){ //that means player one has won
              win = true;
          }
      }

      else if(turn%2==0){ //Player Two's turn
          cout<<endl;
          cout<<"It's PLAYER TWO's turn"<<endl;

          cout<<endl;
          cout<<"  --ENEMIES BOARD--"<<endl;
          p1->printRBoard();
          cout<<"--------------------"<<endl;
          p2->printPBoard();
          cout<<"   --P2's BOARD--"<<endl;

          cout<<endl;
          cout<<"Enter a target(Ex. A3): "<<endl;
          getline(cin, pMove);
          int *x = new int;
          int *y = new int;

          //attacking the other player
          while(!p1->checkTarget(pMove, x, y)){
              cout<<endl;
              cout<<" ---Invalid Target---"<<endl;
              cout<<"Enter a target(Ex. A3): "<<endl;
              getline(cin, pMove);
          }
          //they have a valid target
          cout<<p1->checkMove(p2->getName(), *x, *y)<<endl;
          if (p1->getShipCount() == 0){ //that means player two has won
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
      printNewLine(5);

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
}

int main()
{
    cout<<"Welcome to BattleShip!"<<endl;
    Player *p1 = new Player("Player 1");
    Player *p2 = new Player("Player 2");
    Computer *computer = new Computer();

    initialize("Ships.txt", p1, p2, computer);

    ///to ask if player wants to play
    bool game = playDecision(); //true if player wants to play and false otherwise

    //Players creating their boards
    if (game){
        int gameType = gameTypeDecision();

        if (gameType == 1){ //single player
            computer->createBoard();
            cout<<endl;
            cout<<endl;
            cout << "BattleAI has placed their ships!" << endl;
            cout<<endl;
            cout<<endl;
            cout << "Player One's turn to place their ships!" << endl;
            p1->createBoard();
            cout<<endl;

            singlePlayerRun(p1, computer);
        } else { //multiplayer
            cout<<endl;
            cout << "Player One's turn to place their ships!" << endl;
            p1->createBoard();
            cout<<endl;
            p1->clearScreen();
            cout << "Player Two's turn to place their ships!" << endl;
            p2->createBoard();
            p1->clearScreen();

            multiPlayerRun(p1, p2);
        }
    }

    return 0;
}
