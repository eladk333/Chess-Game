#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "Piece.h"
#include "Move.h"

class Board {
public:
    // Constructor
    Board();

    // Sets up the pieces in their starting positions.
    void setupInitialPosition();

    // Displays the current state of the board to the console.
    void display() const;

    // Executes a move on the board.
    void executeMove(const Move& move);

    // Gets the piece at a specific position. Returns nullptr if the square is empty.
    Piece* getPieceAt(Position pos) const;

    bool isValidPosition(Position pos) const;

private:
    // The grid is a 2D vector of unique_ptr to Piece.
    // std::unique_ptr is a smart pointer that automatically manages memory.
    // When a unique_ptr is destroyed, it deletes the object it points to.
    std::vector<std::vector<std::unique_ptr<Piece>>> grid;
};

#endif // BOARD_H

