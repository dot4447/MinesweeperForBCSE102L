class Play {
public:
    // A Recursive Function to play the Minesweeper Game
    bool playMinesweeperUtil(Board& myBoard,
                             Board& realBoard,
                             int mines[][2], int row,
                             int col, int* movesLeft)
    {
        // Base Case of Recursion
        if (myBoard.board[row][col] != '-')
            return (false);

        int i, j;

        // You opened a mine
        // You are going to lose
        if (realBoard.board[row][col] == '*') {
            myBoard.board[row][col] = '*';
            for (i = 0; i < MINES; i++)
                myBoard.board[mines[i][0]][mines[i][1]]
                    = '*';

            myBoard.Display();
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

                for (int d = 0; d < 8; d++) {
                    int newRow = row + dx[d];
                    int newCol = col + dy[d];

                    if (checkValidity(newRow, newCol) == true) {
                        if (realBoard.checkMine(newRow, newCol)
                            == false)
                            playMinesweeperUtil(
                                myBoard, realBoard, mines,
                                newRow, newCol, movesLeft);
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
        printf("The mines locations are-\n");
        realBoard.Display();
        return;
    }

    // A Function to play Minesweeper game
    void playMinesweeper(Board& realBoard, Board& myBoard)
    {
        // Initially the game is not over
        bool gameOver = false;

        // Actual Board and My Board
        // char realBoard[MAXSIDE][MAXSIDE],
        // myBoard[MAXSIDE][MAXSIDE];

        int movesLeft = SIDE * SIDE - MINES, x, y;
        int mines[MAXMINES][2]; // stores (x,y) coordinates
                                // of all mines.

        // Place the Mines randomly
        realBoard.setMines(mines);

        //         If you want to cheat and know
        //         where mines are before playing the game
        //         then uncomment this part

        // cheatMinesweeper(realBoard);

        // You are in the game until you have not opened a
        // mine So keep playing

        int currentMoveIndex = 0;
        while (gameOver == false) {
            printf("Current Status of Board : \n");
            myBoard.Display();
            myBoard.getMove(&x, &y);

            // This is to guarantee that the first move is
            // always safe
            // If it is the first move of the game
            if (currentMoveIndex == 0) {
                // If the first move itself is a mine
                // then we remove the mine from that
                // location
                 
            }

            currentMoveIndex++;

            gameOver = playMinesweeperUtil(
                myBoard, realBoard, mines, x, y,
                &movesLeft);

            if ((gameOver == false) && (movesLeft == 0)) {
                printf("\nYou won !\n");
                gameOver = true;
            }
        }
        return;
    }
};

 
