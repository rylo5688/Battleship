#include "Computer.h"
#include <iostream>
#include <vector>

using namespace std;

Computer::Computer(string s):level(s), Player(0, 5, "Compooooter")
{

}

Computer::~Computer()
{
    //dtor
}

void Computer::createBoard(){ //didn't have to time to create so i just overloaded printName()

}

void Computer::printName(){
    cout<<name<<" level "<<level;
}
