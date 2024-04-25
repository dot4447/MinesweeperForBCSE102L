#include <iostream>
#include <cstring>
using namespace std;
extern int side;
extern int numofmines;

class Play;
bool checkValidity(int row, int col);

void printtest() {
    cout << "test";
}

class Board {       //All Board Settings
    public:
        char **board;       //Creating a 2D char board
        Board() {
            board = new char* [side+1];
            for (int i=0;i<=side;i++) {
                board[i] = new char[side + 1];
                for (int j = 0; j <= side; j++) {
                    board[i][j] = '~';
                }
            }
        }

        bool checkMine(int row, int column) {     //Checks if a point is a mine or not
            if (board[row][column] == '*')
                return true;
            else
                return false;
        }

        void getMove(int *x, int *y) {      //Prompts user for input
            cout << "Enter move coordinates: ";
            cin >> *x;
            cin >> *y;
        }

        int Adjacent(int row, int col, int MineArray[][2]) {        //Counts number of adjacent MineArray to display on board
            int count = 0;
            int adjx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int adjy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

            for (int i=0;i<8;i++) {
                int pointx = row + adjx[i];
                int pointy = col + adjy[i];
                if (checkValidity(pointx, pointy)) {
                    if (checkMine(pointx, pointy))
                        count++;        //Increase number of adjacent MineArray for every adjacent VALID cell which has a mine
                }
            }
            return count;
        }

        void display() {        //Prints board
            int i, j;
            cout<<"    ";
            for (i=0;i<side;i++) {
                cout<<i<<" ";
            }
            cout<<"\n";
            for (i=0;i<side;i++) {
                cout<<i<<"   ";
                for (j=0;j<side;j++) {
                    cout<<board[i][j]<<" ";
                }
                cout<<"\n";
            }
        }

        void setMines(int MineArray[][2]) {     //Initialises the Board
            bool Locations[side*side];
            memset(Locations, false, sizeof(Locations));
            for (int i=0;i<numofmines;i++) {
                int random = rand() % (side * side);
                int x = random / side;
                int y = random % side;
                if (!Locations[random]) {
                    MineArray[i][0] = x;
                    MineArray[i][1] = y;
                    board[MineArray[i][0]][MineArray[i][1]] = '*';
                    Locations[random] = true;
                }
                else {
                    i--;
                }
            }
        }
};
