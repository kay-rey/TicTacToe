////////////////////////////////////////////////////////////////////////////////
// board.cc : Game of Tic Tac Toe
// Copyright (C) 2018 Garo Bournoutian
// San Francisco State University
//
// ALL YOUR WORK SHOULD BE DONE IN THIS FILE
//
// Student Name: Kevin Baltazar Reyes
// Student ID: 916353599
// Student Email: kreyes6@mail.sfsu.edu
////////////////////////////////////////////////////////////////////////////////


#include "board.h"
#include <cstdlib>   // std::exit and EXIT_FAILURE macro
#include <iostream>  // std::cout, std::cin, std::cerr, std::endl

using namespace std;

// Constructor
//   size: the size of the grid (i.e. size x size)
// 1. Verify that size is >= 3 and <= 10. If not, print an error message to
//    cerr and call exit(EXIT_FAILURE) to terminate the program.
// 2. Dynamically allocate the 2D array named grid_. If there are any
//    allocation errors (e.g. bad_alloc exception), print an error
//    message to cerr and call exit(EXIT_FAILURE) to terminate the program.
// 3. Initialize all the values within the 2D array to be ' ' (a space).
Board::Board(int size) {
    if (size >= 3 && size <= 10) {                    //checks if the size inputted is between 3 and 10 (inclusively)
        size_ = size;
        try {                                        //try is to check if array is being allocated correctly
            grid_ = new char *[size];                //makes new char rows
            for (int i = 0; i < size; ++i) {
                grid_[i] = new char[size];            //makes columns for each char row
                for (int j = 0; j < size; ++j) {
                    grid_[i][j] = ' ';                //initializes the array fields
                }
            }
        }
        catch (bad_alloc &e) {                        //catches if there is a bad memory allocation
            cerr << "Allocation failed: " << e.what() << '\n';
            exit(EXIT_FAILURE);
        }
    } else {
        cerr << "Size can only be an integer between 3 and 10 (inclusively)" << endl;
        exit(EXIT_FAILURE);
    }
}

// Destructor
// 1. De-allocate the 2D array
Board::~Board() {
    for (int i = 0; i < size_; ++i) {
        //		for (int j = 0; j < size_; ++j) {
        //			grid_[i][j] = NULL; // Make each individual entry NULL
        //		}
        delete[] grid_[i]; // Delete the row
    }
    // Finally delete the 2D array itself
    delete[] grid_;
}


// Prints the current board to the screen
// The board should have numbers to indicate the rows and columns, and the
// current values at each position should be displayed (i.e. blank, X, or O).
// This should look something like this (for size=3):
//    0   1   2
//  +---+---+---+
// 0| X |   | O |
//  +---+---+---+
// 1| O |   | X |
//  +---+---+---+
// 2|   | X | O |
//  +---+---+---+
void Board::Display() {
    cout << "  ";                            //draws part of board with the top numbers
    for (int i = 0; i < size_; ++i) {
        cout << "   " << i;
    }
    cout << endl;

    cout << "   ";
    for (int i = 0; i < size_; ++i) {
        cout << "+---";
    }
    cout << "+" << endl;

    for (int i = 0; i < size_; ++i) {        //draws columns and adds their numbers
        cout << " " << i << " | ";
        for (int j = 0; j < size_; ++j) {
            cout << grid_[i][j] << " | ";    //prints every location of the grid
        }
        cout << endl << "   ";
        for (int k = 0; k < size_; ++k) {
            cout << "+---";
        }
        cout << "+" << endl;
    }
}

// Marks the player in the given row and column and returns true on success.
// If the position is invalid or already occupied, print an error to cerr and
// return false.
bool Board::Mark(Player player, int row, int column) {
    if ((row >= 0 && row < size_) && (column >= 0 && column < size_) && grid_[row][column] == ' ') { //make sure that the column and row are correct values as well as check that the entry is a space to continue
        if (player == Player::X) {                          //checks if player is X, if so then print out an 'X', if not then print out a 'O'
            grid_[row][column] = 'X';
        } else {
            grid_[row][column] = 'O';
        }
        return true;
    } else {
        cerr << "Position is invalid or space is already occupied" << endl << endl;     //if entry is too big or already occupied, print out error code and let that same player try again until they enter correct input
    }
    return false;
}

// Returns the winner if they have won, or indicates if the game is still in
// progress or ended in a stalemate (see enum class Winner for details).
Winner Board::CheckWinner() {
    // Your code goes here
    for (int i = 0; i < size_; ++i)            //check rows
    {
        int countRowX = 0;                      //row and column counts are reset after every row
        int countRowO = 0;
        for (int j = 0; j < size_; ++j) {
            if (grid_[i][j] == 'X') {        //checks if X won
                countRowX++;
            }
            if (grid_[i][j] == 'O') {        //checks for O
                countRowO++;
            }
            if (countRowX == size_) {
                return Winner::X;
            }
            if (countRowO == size_) {
                return Winner::O;
            }
        }
    }

    for (int i = 0; i < size_; ++i)  //check columns
    {
        int countX = 0;                 //row and column counts are reset after every column
        int countO = 0;
        for (int j = 0; j < size_; ++j) {
            if (grid_[j][i] == 'X') {
                countX++;
            } else if (grid_[j][i] == 'O') {
                countO++;
            }
            if (countX == size_) {
                return Winner::X;
            }
            if (countO == size_) {
                return Winner::O;
            }
        }
    }

    int countX = 0;                    //check for diagonals
    int countO = 0;
    for (int i = 0; i < size_; ++i) {    //check for diagonal starting from top left to bottom right
        if (grid_[i][i] == 'X') {           //checking diagonal by checking each row and its number
            countX++;
        } else if (grid_[i][i] == 'O') {
            countO++;
        }
    }
    if (countX == size_) {
        return Winner::X;
    }
    if (countO == size_) {
        return Winner::O;
    }

    int countX2 = 0;
    int countO2 = 0;
    for (int i = 0; i < size_; ++i) {        //check for top right to bottom left diagonal
        int j = size_ - i - 1;              //for each row look at the entry that is size - row number to calculate the diagonal
            if (grid_[i][j] == 'X') {
                countX2++;
            } else if (grid_[i][j] == 'O') {
                countO2++;
            }
    }
    if (countX2 == size_) {
        return Winner::X;
    }
    if (countO2 == size_) {
        return Winner::O;
    }

    int stalemateCounter = 0;
    int boardTotal = size_ * size_;        //boardTotal
    for (int i = 0; i < size_; ++i)        //check for stalemate
    {
        for (int j = 0; j < size_; ++j) {
            if (grid_[j][i] != ' ') {
                stalemateCounter++;
            }
        }
    }

    if (stalemateCounter == boardTotal) {        //checks for stalemate
        return Winner::STALEMATE;                //calls stalemate as winner if in stalemate
    }

    return Winner::STILL_PLAYING;
}

