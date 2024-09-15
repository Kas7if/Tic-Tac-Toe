/* Kashif Mohammed
LAB 8 implementing a new function to tic tac toe project */
// Function to choose a square on the board for Player vs AI mode
#include <iostream>
#include <fstream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <limits>  // for numeric_limits

using namespace std;

char board[3][3] = {{'1', '2', '3'},
                    {'4', '5', '6'},
                    {'7', '8', '9'}};

ofstream outputFile("lab8wins.txt");

// Enumeration for game mode
enum GameMode {
    PLAYER_VS_PLAYER,
    PLAYER_VS_AI
};

// Function to display the Tic-Tac-Toe board
void displayBoard() {
    cout << "Tic-Tac-Toe Board:" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check for a win condition
bool win(char player) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            outputFile << "Player " << player << " wins!" << endl;
            return true; // Winning row or column
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        outputFile << "Player " << player << " wins!" << endl;
        return true; // Winning diagonal
    }
    return false;
}

// Function to check for a draw condition
bool draw() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false; // There are still empty squares, game is not a draw
            }
        }
    }
    outputFile << "The game is a draw!" << endl;
    cout << "The game is a draw!" << endl;
    return true;
}

// Function to choose a square on the board for Player vs Player mode
bool choosePlayer(char player) {
    int choice;
    cout << "Player " << player << ", choose a square (1-9): ";
    cin >> choice;

    if (choice < 1 || choice > 9 || board[(choice - 1) / 3][(choice - 1) % 3] == 'X' ||
        board[(choice - 1) / 3][(choice - 1) % 3] == 'O') {
        cout << "Invalid choice! Please choose again." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    } else {
        board[(choice - 1) / 3][(choice - 1) % 3] = player;
        outputFile << "Player " << player << " chose square " << choice << endl;
        if (win(player)) {
            cout << "Player " << player << " wins!" << endl;
            outputFile << "Player " << player << " wins!" << endl;
            return true;
        } else if (draw()) {
            return true;
        }
        return false;
    }
}

// Function to choose a square on the board for Player vs AI mode
bool chooseAI(char player) {
    int choice;
    if (player == 'X') {
        cout << "Player " << player << ", choose a square (1-9): ";
        cin >> choice;
    } else {
        while (true) {
            choice = rand() % 9 + 1; // AI makes a random move
            if (board[(choice - 1) / 3][(choice - 1) % 3] != 'X' &&
                board[(choice - 1) / 3][(choice - 1) % 3] != 'O') {
                break;
            }
        }
        cout << "AI chose square " << choice << endl;
    }

    if (choice < 1 || choice > 9 || board[(choice - 1) / 3][(choice - 1) % 3] == 'X' ||
        board[(choice - 1) / 3][(choice - 1) % 3] == 'O') {
        cout << "Invalid choice! Please choose again." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    } else {
        board[(choice - 1) / 3][(choice - 1) % 3] = player;
        outputFile << "Player " << player << " chose square " << choice << endl;
        if (win(player)) {
            cout << "Player " << player << " wins!" << endl;
            outputFile << "Player " << player << " wins!" << endl;
            return true;
        } else if (draw()) {
            return true;
        }
        return false;
    }
}

int main() {
    srand(time(0)); // Seed for random number generation

    GameMode gameMode;
    char currentPlayer = 'X';

    cout << "Select game mode:" << endl;
    cout << "1. Player vs Player" << endl;
    cout << "2. Player vs AI" << endl;
    int modeChoice;
    cin >> modeChoice;

    if (modeChoice == 2) {
        gameMode = PLAYER_VS_AI;
    } else {
        gameMode = PLAYER_VS_PLAYER;
    }

    displayBoard();

    bool playAgain = true;

    while (playAgain) {
        // Reset the board for a new game
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = '1' + i * 3 + j;
            }
        }

        currentPlayer = 'X'; // Reset the player
        displayBoard();      // Display the board for the new game

        while (true) {
            if (gameMode == PLAYER_VS_PLAYER) {
                if (choosePlayer(currentPlayer))
                    break;
            } else {
                if (chooseAI(currentPlayer))
                    break;
            }
            displayBoard();
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
        displayBoard();

        char response;
        cout << "Do you want to play again? (y/n): ";
        cin >> response;

        if (response != 'y' && response != 'Y') {
            playAgain = false;
        }
    }

    outputFile.close();
    return 0;
}
