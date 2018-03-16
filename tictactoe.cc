////////////////////////////////////////////////////////////////////////////////
// tictactoe.cc : Game of Tic Tac Toe
// Copyright (C) 2018 Garo Bournoutian
// San Francisco State University
//
// DO *NOT* EDIT THIS FILE
//
////////////////////////////////////////////////////////////////////////////////

#include "board.h"

#include <iostream>
#include <limits>

using namespace std;

int main() {
    int size;
    cout << "What size board? ";
    cin >> size;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid data. What size board? ";
        cin >> size;
    }
    cout << endl;

    // Create the board
    Board board(size);

    // Display the initial empty board
    board.Display();

    Winner winner;
    Player player = Player::X;
    do {
        int row, column;
        cout << "Enter a row and column (space separated): ";
        cin >> row >> column;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Not a valid number. Please try again." << endl;
            continue;
        }
        cout << endl;
        if (board.Mark(player, row, column)) {
            // If the action was successful, switch the current player
            player = (player == Player::X ? Player::O : Player::X);
        }
        board.Display();
    } while ((winner = board.CheckWinner()) == Winner::STILL_PLAYING);

    switch (winner) {
        case Winner::X: cout << "Player X won!" << endl; break;
        case Winner::O: cout << "Player O won!" << endl; break;
        case Winner::STALEMATE: cout << "Stalemate!" << endl; break;
        default: break;
    }

    return 0;
}
