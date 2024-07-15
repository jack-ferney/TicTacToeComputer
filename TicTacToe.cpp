#include <iostream>
#include <string>
#include <random>
using namespace std;

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

bool gameOver = false;

int drawChecker = 0;

string lastPlayer = " ";

void printBoard() {
    cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "----------" << endl;
    cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "----------" << endl;
    cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

void checkGame() {
    drawChecker = 0;
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] & board[i][1] == board[i][2] & board[i][0] != ' ') {
            gameOver = true;
            return;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] & board[1][i] == board[2][i] & board[0][i] != ' ') {
            gameOver = true;
            return;
        }
    }
    if (board[0][0] == board[1][1] & board[1][1] == board[2][2] & board[0][0] != ' ') {
        gameOver = true;
        return;
    }
    if (board[0][2] == board[1][1] & board[1][1] == board[2][0] & board[0][2] != ' ') {
        gameOver = true;
        return;
    }
    for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			if (board[i][k] != ' ') {
                drawChecker++;
			}
		}
	}
    if (drawChecker == 9) {
        gameOver = true;
    }
}

void PlayerTurn() {
    cout << "\n\n";
    int choice;
    cout << "\n\nX's turn!\n\nEnter your row and column number: ";
    cin >> choice;
    int row = (choice / 10) - 1;
    int column = (choice % 10) - 1;
    if (board[row][column] != ' ') {
        cout << "That space is already taken!!! Pick another...";
        PlayerTurn();
    } else {
        board[row][column] = 'X';
        cout << "\n\n";
        printBoard();
    }
    lastPlayer = "Player";
    checkGame();
}

void ComputerTurn() {
    cout << "\n\n";
    if (lastPlayer == " ") {
        cout << "\n\nComputer's turn!\n\n";
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr(0, 2);
        board[distr(gen)][distr(gen)] = 'O';
        printBoard();
        return;
    }
    int choice = -1;
    cout << "\n\nComputer's turn!\n\n";
    // Check rows for a potential win
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][0] != ' ' && board[i][2] == ' ') ||
            (board[i][1] == board[i][2] && board[i][1] != ' ' && board[i][0] == ' ') ||
            (board[i][0] == board[i][2] && board[i][0] != ' ' && board[i][1] == ' ')) {
            for (int k = 0; k < 3; k++) {
                if (board[i][k] == ' ') {
                    choice = i * 10 + k;
                    break;
                }
            }
            if (choice != -1) {
                break;
            }
        }
    }

    // Check columns for a potential win
    if (choice == -1) {
        for (int i = 0; i < 3; i++) {
            if ((board[0][i] == board[1][i] && board[0][i] != ' ' && board[2][i] == ' ') ||
                (board[1][i] == board[2][i] && board[1][i] != ' ' && board[0][i] == ' ') ||
                (board[0][i] == board[2][i] && board[0][i] != ' ' && board[1][i] == ' ')) {
                for (int k = 0; k < 3; k++) {
                    if (board[k][i] == ' ') {
                        choice = k * 10 + i;
                        break;
                    }
                }
                if (choice != -1) {
                    break;
                }
            }
        }
    }

    // Check diagonals for a potential win
    if (choice == -1) {
        if ((board[0][0] == board[1][1] && board[0][0] != ' ' && board[2][2] == ' ') ||
            (board[1][1] == board[2][2] && board[1][1] != ' ' && board[0][0] == ' ') ||
            (board[0][0] == board[2][2] && board[0][0] != ' ' && board[1][1] == ' ')) {
            for (int i = 0; i < 3; i++) {
                if (board[i][i] == ' ') {
                    choice = i * 11;
                    break;
                }
            }
        }
    }

    if (choice == -1) {
        if ((board[0][2] == board[1][1] && board[0][2] != ' ' && board[2][0] == ' ') ||
            (board[1][1] == board[2][0] && board[1][1] != ' ' && board[0][2] == ' ') ||
            (board[0][2] == board[2][0] && board[0][2] != ' ' && board[1][1] == ' ')) {
            if (board[0][2] == ' ') {
                choice = 2;
            } else if (board[1][1] == ' ') {
                choice = 11;
            } else if (board[2][0] == ' ') {
                choice = 20;
            }
        }
    }

    // If no winning move is found, choose the first available space (simple AI logic)
    if (choice == -1) {
        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                if (board[i][k] == ' ') {
                    choice = i * 10 + k;
                    break;
                }
            }
            if (choice != -1) {
                break;
            }
        }
    }
    int row = choice / 10;
    int column = choice % 10;
    board[row][column] = 'O';
    printBoard();
    lastPlayer = "Computer";
    checkGame();
}

int main() {
    cout << "\n\n";

    printBoard();
    while (!gameOver) {
        ComputerTurn();
        if (gameOver) {
            break;
        }
        PlayerTurn();
    }
    if (drawChecker == 9) {
        cout << "\n\nDraw... No winner!\n\n";
    } else {
        cout << "\n\n" + lastPlayer + " is the winner!!!\n\n";
    }
    return 0;
}