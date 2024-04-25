#include <iostream>
#include <cstring>
using namespace std;
extern int side;
extern int numofmines;

class Board;
bool checkValidity(int row, int col);

class Play {
public:
    // A Recursive Function to play the Minesweeper Game
    bool playMinesweeperUtil(Board& myBoard, Board& realBoard, int mines[][2], int row, int col, int* movesLeft)
    {
        // Base Case of Recursion
        if (myBoard.board[row][col] != '~')
            return (false);

        int i, j;
        // You opened a mine
        // You are going to lose
        if (realBoard.board[row][col] == '*') {
            myBoard.board[row][col] = '*';
            for (i = 0; i < numofmines; i++)
                myBoard.board[mines[i][0]][mines[i][1]] = '*';

            myBoard.display();
            printf("\nYou lost!\n");
            return (true);
        }
        else {
            // Calculate the number of adjacent mines and
            // put it on the board
            int count = realBoard.Adjacent (
                row, col, mines);
            (*movesLeft)--;

            myBoard.board[row][col] = count + '0';
            if (!count) {
                int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
                int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

                for (int d = 0; d < 8; d++) {int newRow = row + dx[d]; int newCol = col + dy[d];
                    if (checkValidity(newRow, newCol) == true) {
                        if (realBoard.checkMine(newRow, newCol) == false)
                            playMinesweeperUtil(myBoard, realBoard, mines, newRow, newCol, movesLeft);
                    }
                }
            }
            return (false);
        }
    }
    // A Function to cheat by revealing where the mines are
    // placed.
    void cheatMinesweeper(Board& realBoard)
    {
        cout<<"The mines locations are:\n";
        realBoard.display();
        return;
    }
    // A Function to play Minesweeper game
    void StartGame(Board& realBoard, Board& myBoard)
    {
        int x, y;
        // Initially the game is not over
        bool gameOver = false;
        int movesLeft = side * side - numofmines;
        int mines[numofmines][2]; 
        // Place the Mines randomly
        realBoard.setMines(mines);
        // You are in the game until you have not opened a
        // mine So keep playing
        int currentMoveIndex = 0;
        while (gameOver == false) {
            cout<<"Current Status of Board: \n";
            myBoard.display();
            myBoard.getMove(&x, &y);
            currentMoveIndex++;
            gameOver = playMinesweeperUtil(myBoard, realBoard, mines, x, y, &movesLeft);
            if ((gameOver == false) && (movesLeft == 0)) {
                cout<<"\nYou won !\n";
                gameOver = true;
            }
        }
        return;
    }
};
