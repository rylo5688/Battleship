#ifndef PLAYERINFO_H
#define PLAYERINFO_H
#include "Player.h"
#include <iostream>

using namespace std;

class PlayerInfo: public Player
{
    public:
        PlayerInfo(string n);
        virtual ~PlayerInfo();
    protected:
    private:
        string name;
        vector<int> targetNum;
        vector<string> target;
};


#endif // PLAYERINFO_H
