#include "../include/Player.h"
#include "../include/Ship.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

Player::Player()
{
    index = 0;
    shipCount = 5;
    name = "Player";
}

Player::Player(int i, int sC, string n){
    index = i;
    shipCount = sC;
    name = n;
}

Player::Player(string n){
    index = 0;
    shipCount = 5;
    name = n;
}

Player::~Player()
{
    //dtor
}

void Player::addShip(Ship s){
    ships[index] = s;
    index++;
}

void Player::printShips(){ //
    for (int i = 0; i < index; i++){
        ships[i].print();
    }
}

//when players will place their ships
void Player::createBoard(){ //should be called after ships array has been initialized so that players may place their ships
    int placed = 0;
    string used[5];
    vector<Ship> choices; //vector to hold ship choices

    for (int i = 0; i < 5; i++){ //add ship values to the vector
        choices.push_back(ships[i]);
    }

    while (placed != 5){ //loops until all 5 ships have been placed
        cout<<endl;
        cout<<"Enter which ship you'd like to place(capitalization matters)! "<<endl;
        printChoices(choices);

        string input;
        int cIndex; //index of the choice
        int *cIndexPointer = &cIndex;
        getline(cin, input);
        while(!checkChoice(choices, input, cIndexPointer)){
            cout<<endl;
            cout<<" ---Invalid Input---"<<endl;
            cout<<"Enter which ship you'd like to place(capitalization matters)! "<<endl;
            printChoices(choices);
            getline(cin, input);
        }
        //now they have made a choice and we have the index of the choice

        cout<<endl;
        pBoard.printBoard();
        cout<<endl;
        cout<<"Pick the coordinates where you'd like to place your ship(Ex. A3)! "<<endl;
        string coords;
        getline(cin, coords);
        int x;
        int *xPointer = &x;
        int y;
        int *yPointer = &y;
        int l = choices[cIndex].getLength();

        while(!checkCoords(coords, xPointer, yPointer)){ //checks for valid coordinate input
            cout<<endl;
            cout<<"---Invalid Input---"<<endl;
            pBoard.printBoard();
            cout<<endl;
            cout<<"Pick the coordinates where you'd like to place your ship(Ex. A3)! "<<endl;
            getline(cin, coords);
        }

        //now they have put in valid coordinates
        cout<<endl;
        cout<<"What direction would you like your ship(u,d,l,r) from "<<coords<<"? "<<endl;
        string dir;
        getline(cin, dir);
        while(dir != "u" and dir != "d" and dir != "l" and dir != "r"){ //making sure they entered a direction before we check if the placement is correct
            cout<<endl;
            cout<<"---Invalid Input---"<<endl;
            cout<<"What direction would you like your ship(u,d,l,r) from "<<coords<<"? "<<endl;
            getline(cin, dir);
        }

        //get the index of the choice made in the ships array of the Player object
        int shipsIndex;
        for (int i = 0; i < 5; i++){
            if (ships[i].getName().substr(0, 2) == input){
                shipsIndex = i;
            }
        }

        //check placement
        while(!checkPlacement(dir, xPointer, yPointer, l, shipsIndex)){
            cout<<endl;
            cout<<" ---Invalid Placement---"<<endl;
            pBoard.printBoard();
            cout<<"Enter in another direction(u,d,l,r) from "<<coords<<"! "<<endl;
            getline(cin, dir);
        }

        pBoard.printBoard();



        ///take out the choice from choices
        choices.erase(choices.begin()+cIndex);
        placed++;
    }
}

void Player::printChoices(vector<Ship> s){ //prints the available choices
    for(int i = 0; i < s.size(); i++){
        s[i].print();
    }
}

bool Player::checkChoice(vector<Ship> s, string uIn, int *n){ //checks if user input matches any of the ship choices
    for (int i = 0; i < s.size(); i++){
        if (s[i].getName().substr(0, 2) == uIn){
            *n = i;
            return true;
        }
    }
    return false;
}

bool Player::checkCoords(string c, int *col, int *row){
    string xCoords = "ABCDEFGHIJ";
    string yCoords = "0123456789";

    for (int x = 0; x < 10; x++){
        for (int y = 0; y < 10; y++){
            string temp = xCoords.substr(x, 1) + yCoords.substr(y, 1); //gets valid coordinates first one is A0
            if (c == temp){ //means they entered a correct coordinate
                if (checkBoard(pBoard, y+1, x+1) != "o"){ //checks if they coordinate they entered has a ship on it already
                    return false;
                }
                *col = x+1;
                *row = y+1;
                return true;
            }
        }
    }
    return false;
}

bool Player::checkTarget(string c, int *col, int *row){
    string xCoords = "ABCDEFGHIJ";
    string yCoords = "0123456789";
    for (int x = 0; x < 10; x++){
        for (int y = 0; y < 10; y++){
            string temp = xCoords.substr(x, 1) + yCoords.substr(y, 1); //gets valid coordinates first one is A0
            if (c == temp){ //means they entered a correct coordinate
                if (checkBoard(rBoard, y+1, x+1) == "X" or checkBoard(rBoard, y+1, x+1) == "M"){
                    return false;
                }
                *col = x+1;
                *row = y+1;
                return true;
            }
        }
    }

    return false;
}

bool Player::checkPlacement(string direction, int *col, int *row, int length, int sIndex){
    if (direction == "u"){ //up direction
        if (*row - length + 1 < 1){ //out of bounds check, need to subtract one from length cause we start at the given coords
            return false;
        }
        //now check for ships in the way
        for (int r = *row; r > *row - length; r--){
            if (checkBoard(pBoard, r, *col) != "o"){ //this means there's a ship in the way
                return false;
            }
        }
        //ship placement works!!!
        //so now update that ship and board object to have those coords and return true for placement
        for (int r = *row; r > *row - length; r--){
            pBoard.changeBoard(*col, r, "|");
            ships[sIndex].addCoordinates(*col, r);
        }
        return true;
    }
    else if (direction == "d"){ //down direction
        if (*row + length - 1 > 11){ //out of bounds check, need to subtract one from length cause we start at the given coords
            return false;
        }
        //now check for ships in the way
        for (int r = *row; r < *row + length; r++){
            if (checkBoard(pBoard, r, *col) != "o"){ //this means there's a ship in the way
                return false;
            }
        }
        //ship placement works!!!
        //so now update that ship and board object to have those coords and return true for placement
        for (int r = *row; r < *row + length; r++){
            pBoard.changeBoard(*col, r, "|");
            ships[sIndex].addCoordinates(*col, r);
        }
        return true;
    }
    else if (direction == "l"){ //left direction
        if (*col - length + 1 < 1){ //out of bounds check, need to subtract one from length cause we start at the given coords
            return false;
        }
        //now check for ships in the way
        for (int c = *col; c > *col - length; c--){
            if (checkBoard(pBoard, *row, c) != "o"){ //this means there's a ship in the way
                return false;
            }
        }
        //ship placement works!!!
        //so now update that ship and board object to have those coords and return true for placement
        for (int c = *col; c > *col - length; c--){
            pBoard.changeBoard(c, *row, "-");
            ships[sIndex].addCoordinates(c, *row);
        }
        return true;
    }
    else if (direction == "r"){
        if (*col + length - 1 > 11){ //out of bounds check, need to subtract one from length cause we start at the given coords
            return false;
        }
        //now check for ships in the way
        for (int c = *col; c < *col + length; c++){
            if (checkBoard(pBoard, *row, c) != "o"){
                return false;
            }
        }
        //ship placement works!!!
        //so now update that ship and board object to have those coords and return true for placement
        for (int c = *col; c < *col + length; c++){
            pBoard.changeBoard(c, *row, "-");
            ships[sIndex].addCoordinates(c, *row);
        }
        return true;
    }
    return false;
}

void Player::printRBoard(){
    rBoard.printBoard();
}

void Player::printPBoard(){
    pBoard.printBoard();
}

string Player::checkMove(int c, int r){
    string target = checkBoard(pBoard, r, c);
    if (target == "|" or target == "-"){
        pBoard.changeBoard(c, r, "X"); //"X" is a hit
        rBoard.changeBoard(c, r, "X"); //"X" is a hit

        //getting the index of the ship that was hit
        int sIndex;
        for (int i = 0; i < 5; i++){
            if (ships[i].checkShip(c, r)){
                sIndex = i;
                break;
            }
        }
        ships[sIndex].hit(c, r); //takes out those ship coordinates
        if (!ships[sIndex].alive()){
            cout<<"You SANK the enemies "<<ships[sIndex].getName()<<endl;
            shipCount--;
        }
        clearScreen();
        return "You got a hit!";
    }
    else{
        clearScreen();
        pBoard.changeBoard(c, r, "M"); //"M" is a miss
        rBoard.changeBoard(c, r, "M"); //"M" is a miss
        return "You missed!";
    }
}

int Player::getShipCount(){
    return shipCount;
}

void Player::printName(){
    cout << name;
}

void Player::clearScreen(){
    //5 line buffer
    for (int i = 0; i < 24; i++){
      cout<<endl;
    }
}
