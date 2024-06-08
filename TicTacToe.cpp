#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];

void initializeBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << "|";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "-----\n";
    }
    cout << "\n";
}

bool isBoardFull() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == ' ') return false;
    return true;
}

bool checkWin(char player) {
    for (int i = 0; i < SIZE; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

bool makeMove(int row, int col, char player) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
        board[row][col] = player;
        return true;
    }
    return false;
}

void playerTurn(char player) {
    int row, col;
    do {
        cout << "Player " << player << ", enter row and column (0-2, space separated): ";
        while (!(cin >> row >> col)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input. Please enter numbers only.\n";
            cout << "Player " << player << ", enter row and column (0-2, space separated): ";
        }
    } while (!makeMove(row, col, player));
}

void computerTurn(char player) {
    int row, col;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!makeMove(row, col, player));
    cout << "Computer placed an " << player << " in position " << row << ", " << col << endl;
}

void playGame() {
    char player1 = 'X', player2 = 'O';
    bool player1Turn = true;
    bool againstComputer = false;

    cout << "Play against computer? (1 for Yes, 0 for No): ";
    cin >> againstComputer;

    initializeBoard();
    printBoard();

    while (true) {
        if (player1Turn) {
            cout << "Player 1's turn:\n";
            playerTurn(player1);
        } else {
            if (againstComputer) {
                computerTurn(player2);
            } else {
                cout << "Player 2's turn:\n";
                playerTurn(player2);
            }
        }
        printBoard();

        if (checkWin(player1Turn ? player1 : player2)) {
            cout << "Player " << (player1Turn ? "1" : (againstComputer ? "Computer" : "2")) << " wins!\n";
            break;
        } else if (isBoardFull()) {
            cout << "The game is a draw.\n";
            break;
        }

        player1Turn = !player1Turn;
    }
}

int main() {
    srand(time(0)); 
    char playAgain = '
