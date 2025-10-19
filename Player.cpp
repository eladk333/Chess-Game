#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

Move HumanPlayer::getMove(const Board& board) const {
    string moveStr;
    Position start, end;
    bool validInput = false;

    while (!validInput) {
        cout << "Enter your move:";
        cin >> moveStr;

        // Basic validation: input must be 4 characters long
        if (moveStr.length() == 4) {
            // Convert algebraic notation to grid coordinates
            // 'a' corresponds to column 0, 'b' to 1, etc.
            int startCol = moveStr[0] - 'a';
            // '1' corresponds to row 7, '2' to 6, etc.
            int startRow = 8 - (moveStr[1] - '0');

            int endCol = moveStr[2] - 'a';
            int endRow = 8 - (moveStr[3] - '0');

            // Check if the coordinates are within the board
            if (startCol >= 0 && startCol < 8 && startRow >= 0 && startRow < 8 &&
                endCol >= 0 && endCol < 8 && endRow >= 0 && endRow < 8)
            {
                start = {startRow, startCol};
                end = {endRow, endCol};
                validInput = true;
            } else {
                cout << "Invalid move format. Coordinates are off the board. Please try again." << endl;
            }
        } else {
            cout << "Invalid move format. Please use 4 characters, like 'e2e4'." << endl;
        }
    }
    return {start, end};
}

