#include "../include/Game.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>

Game::Game(string fileName){
    player1 = new Player("Player 1");
    player2 = new Player("Player 2");
    computer = new Computer();

    ifstream shipData;
    shipData.open("./src/" + fileName + ".txt");
    if(shipData.fail()){
        cout<<"something went wrong"<<endl;
    }
    else{
        string line;

        //Getting all the ship names and sizes from Ships.txt
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

            player1->addShip(temp);
            player2->addShip(temp);
            computer->addShip(temp);
        }
    }
}

Game::~Game(){
    delete player1;
    delete player2;
    delete computer;
}

void Game::singlePlayerSetup(){
    //Computer setting up its board
    computer->createBoard();
    cout<<endl;
    cout<<endl;
    cout << "BattleAI has placed its ships!" << endl;
    cout<<endl;
    cout<<endl;

    //getting player one's name
    string name;
    cout<<"Enter in your in-game name: ";
    cin>>name;
    cin.ignore();
    player1->setName(name);

    cout<<endl;
    cout<<endl;

    //Player 1 setting up their board
    cout << player1->getName() << "'s turn to place their ships!" << endl;
    player1->createBoard();
    cout<<endl;
}

void Game::singlePlayerRun(){
  bool win = false;

  string pMove;
  while(!win){
    printNewLine(2);
    cout << "It's " << player1->getName() << "'s turn" << endl;
    cout<<endl;

    cout << "  --ENEMIES BOARD--" << endl;
    computer->printRBoard();
    cout<< "--------------------"<<endl;
    player1->printPBoard();
    cout << "   --" << player1->getName() << "'s BOARD--" << endl;

    cout<<endl;
    cout<<"Enter a target(Ex. A3): "<<endl;

    getline(cin, pMove);
    int *x = new int;
    int *y = new int;

    //attacking the other player
    while(!computer->checkTarget(pMove, x, y)){
        cout<<endl;
        cout << " ---Invalid Target---" << endl;
        cout << "Enter a target(Ex. A3): " << endl;
        getline(cin, pMove);
    }
    //User has selected a valid target
    player1->clearScreen();
    cout<<computer->checkMove(player1->getName(), *x, *y)<<endl;

    if (computer->getShipCount() == 0){ //that means player one has won
        win = true;
        break;
    }

    string moveOn;
    cout << "Enter 'Y' to move onto the next turn: " << endl;
    getline(cin, moveOn);
    while (moveOn != "Y" and moveOn != "y"){
        cout << "Enter 'Y' to move onto the next turn: " << endl;
        getline(cin, moveOn);
    }

    //Computer attack logic
    printNewLine(3);
    computer->attack(player1);
    printNewLine(3);

    if (player1->getShipCount() == 0){
        win = true;
        break;
    }
  }

  if (win){
      if (computer->getShipCount() == 0){ //Player won
          cout << "Congradulations you beat " << computer->getName() << endl;
          cout << "Would you like to enter a name to add to the list of winners(Y/N): " << endl;
          string answer;
          getline(cin, answer);
          while (answer != "Y" and answer != "y" and answer != "N" and answer != "n"){
              cout << "Would you like to enter a name to add to the list of winners(Y/N): " << endl;
              getline(cin, answer);
          }
          if (answer == "y" or answer == "Y"){
              ofstream winners("winners.txt", ios::app);
              winners<<player1->getName() + '\n';
              winners.close();
              cout << "Thanks for playing!" << endl;
          }
          else{
              cout << "Thanks for playing!" << endl;
          }
      } else { //Computer won
          cout << computer->getName() << " has won." << endl;
          cout << " Better luck next time!" << endl;
      }
  }
}

void Game::multiPlayerSetup(){
    string name;

    //First player entering their name and setting up their board
    cout << "Player 1 enter your in-game name: ";
    cin>>name;
    cin.ignore();
    player1->setName(name);

    cout<<endl;
    cout << player1->getName() << "'s turn to place their ships!" << endl;
    player1->createBoard();
    cout<<endl;
    player1->clearScreen();

    //Second player entering their name and setting up their board
    player2->clearScreen();
    cout << "Player 2 enter your in-game name: ";
    cin>>name;
    cin.ignore();
    player2->setName(name);

    cout << player2->getName() << "'s turn to place their ships!" << endl;
    player2->createBoard();
    player1->clearScreen();
}

void Game::multiPlayerRun(){
  bool win = false;
  ///game begins here
  int turn = 1;
  while(!win){
      printNewLine(5);

      string pMove;
      if (turn%2==1){ //Player One's turn
          cout<<endl;
          cout << "It's " << player1->getName() << "'s turn" << endl;

          cout<<endl;
          cout <<"  --ENEMIES BOARD--" << endl;
          player2->printRBoard();
          cout<<"--------------------"<<endl;
          player1->printPBoard();
          cout << "   --" << player1->getName() << "'s BOARD--" << endl;

          cout<<endl;
          cout << "Enter a target(Ex. A3): " << endl;
          getline(cin, pMove);
          int *x = new int;
          int *y = new int;

          //attacking the other player
          while(!player2->checkTarget(pMove, x, y)){
              cout<<endl;
              cout << " ---Invalid Target---" << endl;
              cout << "Enter a target(Ex. A3): " << endl;
              getline(cin, pMove);
          }

          //they have a valid target
          cout<<player2->checkMove(player1->getName(), *x, *y)<<endl;
          if (player2->getShipCount() == 0){ //that means player one has won
              win = true;
          }
      }

      else if(turn%2==0){ //Player Two's turn
          cout<<endl;
          cout << "It's " << player2->getName() << "'s turn" << endl;

          cout<<endl;
          cout << "  --ENEMIES BOARD--" << endl;
          player1->printRBoard();
          cout << "--------------------" << endl;
          player2->printPBoard();
          cout << "   --" << player2->getName() << "'s BOARD--" << endl;

          cout<<endl;
          cout << "Enter a target(Ex. A3): " << endl;
          getline(cin, pMove);
          int *x = new int;
          int *y = new int;

          //attacking the other player
          while(!player1->checkTarget(pMove, x, y)){
              cout<<endl;
              cout << " ---Invalid Target---" << endl;
              cout << "Enter a target(Ex. A3): " << endl;
              getline(cin, pMove);
          }
          //they have a valid target
          cout<<player1->checkMove(player2->getName(), *x, *y)<<endl;
          if (player1->getShipCount() == 0){ //that means player two has won
              win = true;
              break;
          }

      }

      string moveOn;
      cout << "Enter 'Y' to move onto the next turn: " << endl;
      getline(cin, moveOn);
      while (moveOn != "Y" and moveOn != "y"){
          cout << "Enter 'Y' to move onto the next turn: " << endl;
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
      cout << player1->getName() << "Player One has won the game!" << endl;
      cout << "Would you like to enter a name to add to the list of winners(Y/N): " << endl;
      string answer;
      getline(cin, answer);
      while (answer != "Y" and answer != "y" and answer != "N" and answer != "n"){
          cout << "Would you like to enter a name to add to the list of winners(Y/N): " << endl;
          getline(cin, answer);
      }
      if (answer == "y" or answer == "Y"){
          ofstream winners("winners.txt", ios::app);
          winners<<player1->getName() + '\n';
          winners.close();
          cout << "Thanks for playing!" << endl;
      }
      else{
          cout << "Thanks for playing!" << endl;
      }
  }
  else if (turn%2==0){ //Player 2 has won the game
      cout << player2->getName() << " has won the game!" << endl;
      cout << "Would you like to enter a name to add to the list of winners(Y/N): " << endl;
      string answer;
      getline(cin, answer);
      while (answer != "Y" and answer != "y" and answer != "N" and answer != "n"){
          cout << "Would you like to enter a name to add to the list of winners(Y/N): " << endl;
          getline(cin, answer);
      }
      if (answer == "y" or answer == "Y"){
          ofstream winners("winners.txt", ios::app);
          winners<<player2->getName() + '\n';
          winners.close();
          cout << "Thanks for playing!" << endl;
      }
      else{
          cout << "Thanks for playing!" << endl;
      }
  }
}

//Function for printing n number of new lines
void Game::printNewLine(int n){
  for (int i = 0; i < n; i++){
    cout<<endl;
  }
}
