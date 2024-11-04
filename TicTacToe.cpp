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
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            gameOver = true;
            return;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            gameOver = true;
            return;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        gameOver = true;
        return;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
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

    // Brute force search for computer win
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            if (board[i][k] == ' ' && choice == -1) {
                board[i][k] = 'O';
                checkGame();
                if (gameOver) {
                    gameOver = false;
                    choice = i * 10 + k;
                    board[i][k] = ' ';
                    break;
                }
                board[i][k] = ' ';
            }
        }
    }

    // Brute force search for player win (to block)
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            if (board[i][k] == ' ' && choice == -1) {
                board[i][k] = 'X';
                checkGame();
                if (gameOver) {
                    gameOver = false;
                    choice = i * 10 + k;
                    board[i][k] = ' ';
                    break;
                }
                board[i][k] = ' ';
            }
        }
    }

    // If no winning move is found, choose the first available space
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
        PlayerTurn();
        if (gameOver) {
            break;
        }
        ComputerTurn();
    }
    if (drawChecker == 9) {
        cout << "\n\nDraw... No winner!\n\n";
    } else {
        cout << "\n\n" + lastPlayer + " is the winner!!!\n\n";
    }
    return 0;
}