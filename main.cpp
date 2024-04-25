#include <iostream>
#include <cstring>
#include "computeractions.h"
#include "playeractions.h"
using namespace std;

int side = 9;      //Standard Easy Difficulty
int numofmines = 10;        //It is recommended to only use standard difficulty values (ie mine to side ratios) if changing these values.

bool checkValidity(int row, int column) {
    return ((row >= 0) && (row < side) && (column >= 0) && (column < side));
}

int main() {
    Board User, Actual;
    Play* Game = new Play();
    Game->StartGame(User, Actual);
    return 0;
}
