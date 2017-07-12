#include "../include/Ship.h"
#include <vector>
#include <iostream>
#include <locale>

using namespace std;

Ship::Ship()
{
    //ctor
}

Ship::~Ship()
{
    //dtor
}

Ship::Ship(string n, int l){
    name = n;
    length = l;
}

void Ship::print(){
    cout<<"Ship Name("<<name.substr(0, 2)<<"): "<<name<<", Length: "<<length<<endl;
}

string Ship::getName(){
    return name;
}

int Ship::getLength(){
    return length;
}

void Ship::addCoordinates(int c, int r){
    xCoords.push_back(c);
    yCoords.push_back(r);
}

bool Ship::alive(){
    if (xCoords.size() == 0 and yCoords.size() == 0){
        return false;
    }
    return true;
}

bool Ship::checkShip(int x, int y){
    for (int i = 0; i < xCoords.size(); i++){
        if (xCoords[i] == x and yCoords[i] == y){
            return true;
        }
    }
    return false;
}

void Ship::hit(int x, int y){ //assuming that a hit has been made and checkShip has been called
    int n = xCoords.size();
    for (int i = 0; i < n; i++){
        if (xCoords[i] == x and yCoords[i] == y){
            xCoords.erase(xCoords.begin()+i);
            yCoords.erase(yCoords.begin()+i);
        }
    }
}
