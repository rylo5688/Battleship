#ifndef SHIP_H
#define SHIP_H
#include <iostream>
#include <vector>

using namespace std;

class Ship
{
    public:
        Ship();
        virtual ~Ship();
        Ship(string n, int l);
        void print();
        string getName();
        int getLength();
        void addCoordinates(int c, int r);
        bool alive();
        bool checkShip(int x, int y);
        void hit(int x, int y);
    protected:
    private:
        string name;
        int length;
        vector<int> xCoords;
        vector<int> yCoords;
};

#endif // SHIP_H
