/*
Code made By Mohamed AbdelWahab



Minesweeper Game

made between 8-Aug-25 and 14-Aug-25



*/



//libraries needed
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

const int SIZE = 8;
const char HIDDEN = ' ';
const char BOMB = '*';

// Directions for checking neighbors
int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 }; // directions in x 

int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 }; // in y

struct Cell {
    bool isBomb = false; //boolean variable to check the existence of a bomb
    bool revealed = false;  
    int neighborBombs = 0; 
};

void placeBombs(vector<vector<Cell>>& board, int numBombs) {
    int placed = 0;
    while (placed < numBombs) {
        int r = rand() % SIZE; // max 8
        int c = rand() % SIZE; //max 8 
        if (!board[r][c].isBomb) {
            board[r][c].isBomb = true;
            placed++;
        }
    }
}

void calculateNeighborCounts(vector<vector<Cell>>& board) {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (board[r][c].isBomb) continue;
            int count = 0;
            for (int i = 0; i < 8; i++) {
                int nr = r + dx[i];
                int nc = c + dy[i];
                if (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE && board[nr][nc].isBomb) {
                    count++;
                }
            }
            board[r][c].neighborBombs = count;
        }
    }
}

void printBoard(const vector<vector<Cell>>& board, bool revealAll = false) {  
    cout << "   "; // prints spaces in front
    for (int c = 0; c < SIZE; c++) cout << setw(2)/* extra width 2 */ << c; //for loop that sets the sizes
    cout << "\n";
    for (int r = 0; r < SIZE; r++) {
        cout << setw(2) << r << " ";
        for (int c = 0; c < SIZE; c++) {
            if (revealAll) {
                if (board[r][c].isBomb) cout << " " << BOMB;
                else cout << " " << board[r][c].neighborBombs;
            }
            else {
                if (board[r][c].revealed) cout << " " << board[r][c].neighborBombs;
                else cout << " " << HIDDEN;
            }
        }
        cout << "\n";
    }
}

void revealCell(vector<vector<Cell>>& board, int r, int c) {
    if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) return;
    if (board[r][c].revealed) return;

    board[r][c].revealed = true;

    // Auto-reveal neighbors if 0 bombs nearby
    if (board[r][c].neighborBombs == 0 && !board[r][c].isBomb) {
        for (int i = 0; i < 8; i++) {
            revealCell(board, r + dx[i], c + dy[i]);
        }
    }
}

bool checkWin(const vector<vector<Cell>>& board) {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (!board[r][c].isBomb && !board[r][c].revealed) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    srand(time(0));
    vector<vector<Cell>> board(SIZE, vector<Cell>(SIZE));

    // Random bombs between 10 and 15
    int numBombs = 10 + rand() % 6;
    placeBombs(board, numBombs);
    calculateNeighborCounts(board);

    cout << "=== Minesweeper ===\n";
    cout << "Enter row and column (e.g., 3 4)\n";

    while (true) {
        printBoard(board);
        int r, c;
        cout << "Your move: ";
        cin >> r >> c;

        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) {
            cout << "Invalid coordinates. Try again.\n";
            continue;
        }

        if (board[r][c].isBomb) {
            cout << "BOOM! You hit a bomb!\n";
            printBoard(board, true);
            break;
        }

        revealCell(board, r, c);

        if (checkWin(board)) {
            cout << "Congratulations! You cleared he board!\n";
            printBoard(board, true);
            break;
        }
    }

    return 0;
}
