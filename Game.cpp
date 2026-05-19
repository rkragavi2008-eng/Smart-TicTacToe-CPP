#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

char board[3][3];
char currentPlayer;

// Initialize board
void resetBoard() {
    char count = '1';
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            board[i][j] = count++;
}

// Display board
void displayBoard() {
    cout << "\n";
    cout << " TIC TAC TOE\n";
    cout << "-------------\n";
    for(int i = 0; i < 3; i++) {
        cout << " ";
        for(int j = 0; j < 3; j++) {
            cout << board[i][j];
            if(j < 2) cout << " | ";
        }
        cout << "\n";
        if(i < 2) cout << "---|---|---\n";
    }
    cout << "-------------\n";
}

// Check win
bool checkWin() {
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return true;
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return true;
    }

    if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return true;
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return true;

    return false;
}

// Check draw
bool isDraw() {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

// Switch player
void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

// Player move
void playerMove() {
    int choice;
    while(true) {
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        cin >> choice;

        if(cin.fail() || choice < 1 || choice > 9) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Try again.\n";
            continue;
        }

        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        if(board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = currentPlayer;
            break;
        } else {
            cout << "Cell already taken! Try again.\n";
        }
    }
}

// Computer move (random AI)
void computerMove() {
    int row, col;
    while(true) {
        row = rand() % 3;
        col = rand() % 3;

        if(board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = 'O';
            cout << "Computer chose position " << (row * 3 + col + 1) << "\n";
            break;
        }
    }
}

// Game mode
void playGame(bool vsComputer) {
    resetBoard();
    currentPlayer = 'X';
    bool gameOver = false;

    while(!gameOver) {
        displayBoard();

        if(vsComputer && currentPlayer == 'O') {
            computerMove();
        } else {
            playerMove();
        }

        if(checkWin()) {
            displayBoard();
            if(vsComputer && currentPlayer == 'O')
                cout << "🤖 Computer wins!\n";
            else
                cout << "🎉 Player " << currentPlayer << " wins!\n";
            gameOver = true;
        }
        else if(isDraw()) {
            displayBoard();
            cout << " It's a draw!\n";
            gameOver = true;
        }
        else {
            switchPlayer();
        }
    }
}

// Main function
int main() {
    srand(time(0));
    int choice;
    char playAgain;

    do {
        cout << "\n==== TIC TAC TOE ====\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1)
            playGame(false);
        else if(choice == 2)
            playGame(true);
        else {
            cout << "Invalid choice!\n";
            continue;
        }

        cout << "Play again? (y/n): ";
        cin >> playAgain;

    } while(playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}