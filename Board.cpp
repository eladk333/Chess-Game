#include "Board.h"
#include <iostream>

using namespace std;

Board::Board() {
    
    // Each element is initialized to nullptr by default, meaning the squares are empty.
    grid.resize(8);
    for (int i = 0; i < 8; ++i) {
        grid[i].resize(8);
    }
}

// --- Public Method Implementations ---

void Board::setupInitialPosition() {
    // Clear the board first in case this is called on a non-empty board.
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            grid[r][c] = nullptr;
        }
    }

    // Black pieces.
    grid[0][0] = make_unique<Rook>(PieceColor::BLACK);
    grid[0][7] = make_unique<Rook>(PieceColor::BLACK);
    grid[0][1] = make_unique<Knight>(PieceColor::BLACK);
    grid[0][6] = make_unique<Knight>(PieceColor::BLACK);
    grid[0][2] = make_unique<Bishop>(PieceColor::BLACK);
    grid[0][5] = make_unique<Bishop>(PieceColor::BLACK);
    grid[0][3] = make_unique<Queen>(PieceColor::BLACK);
    grid[0][4] = make_unique<King>(PieceColor::BLACK);
    for (int c = 0; c < 8; ++c) {
        grid[1][c] = make_unique<Pawn>(PieceColor::BLACK);
    }

    // White pieces.
    grid[7][0] = make_unique<Rook>(PieceColor::WHITE);
    grid[7][7] = make_unique<Rook>(PieceColor::WHITE);
    grid[7][1] = make_unique<Knight>(PieceColor::WHITE);
    grid[7][6] = make_unique<Knight>(PieceColor::WHITE);
    grid[7][2] = make_unique<Bishop>(PieceColor::WHITE);
    grid[7][5] = make_unique<Bishop>(PieceColor::WHITE);
    grid[7][3] = make_unique<Queen>(PieceColor::WHITE);
    grid[7][4] = make_unique<King>(PieceColor::WHITE);
    for (int c = 0; c < 8; ++c) {
        grid[6][c] = make_unique<Pawn>(PieceColor::WHITE);
    }
}
bool Board::isValidPosition(Position pos) const {
    // Check if the row and column are within the 8x8 board boundaries.
    return pos.row >= 0 && pos.row < 8 && pos.col >= 0 && pos.col < 8;
}

void Board::display() const {
    cout << "  a b c d e f g h" << endl;
    cout << " +-----------------+" << endl;
    for (int r = 0; r < 8; ++r) {
        cout << 8 - r << "| ";
        for (int c = 0; c < 8; ++c) {
            if (grid[r][c]) {
                cout << grid[r][c]->getCharRepresentation() << " ";
            } else {
                cout << ". ";
            }
        }
        cout << "|" << 8 - r << endl;
    }
    cout << " +-----------------+" << endl;
    cout << "  a b c d e f g h" << endl;
}
void Board::executeMove(const Move& move) {
    // This uses std::move to transfer ownership of the unique_ptr
    // from the start square to the end square.
    // The start square's unique_ptr becomes nullptr after this.
    grid[move.end.row][move.end.col] = std::move(grid[move.start.row][move.start.col]);
}

Piece* Board::getPieceAt(Position pos) const {
    // .get() returns the raw pointer managed by the unique_ptr.
    // It's safe to return a raw pointer here because the Board still owns the memory.
    return grid[pos.row][pos.col].get();
}

