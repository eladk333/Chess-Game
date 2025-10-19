#include "Piece.h"
#include "Board.h"
#include <cctype> 

using namespace std;

// --- Piece Implementation ---
Piece::Piece(PieceColor color, PieceType type) : color(color), type(type) {}
PieceColor Piece::getColor() const { return color; }
PieceType Piece::getType() const { return type; }
char Piece::getCharRepresentation() const {
    char c = ' ';
    switch (type) {
        case PieceType::KING:   c = 'k'; break;
        case PieceType::QUEEN:  c = 'q'; break;
        case PieceType::ROOK:   c = 'r'; break;
        case PieceType::BISHOP: c = 'b'; break;
        case PieceType::KNIGHT: c = 'n'; break;
        case PieceType::PAWN:   c = 'p'; break;
        case PieceType::EMPTY:  c = ' '; break;
    }
    if (color == PieceColor::WHITE) {
        return toupper(c);
    }
    return c;
}

// --- Specific Piece Constructors ---
Pawn::Pawn(PieceColor color) : Piece(color, PieceType::PAWN) {}
Rook::Rook(PieceColor color) : Piece(color, PieceType::ROOK) {}
Knight::Knight(PieceColor color) : Piece(color, PieceType::KNIGHT) {}
Bishop::Bishop(PieceColor color) : Piece(color, PieceType::BISHOP) {}
Queen::Queen(PieceColor color) : Piece(color, PieceType::QUEEN) {}
King::King(PieceColor color) : Piece(color, PieceType::KING) {}

// --- getPossibleMoves Implementations ---

vector<Move> Pawn::getPossibleMoves(Position currentPosition, const Board& board) const {
    vector<Move> moves;
    int direction = (color == PieceColor::WHITE) ? -1 : 1;
    int startRow = (color == PieceColor::WHITE) ? 6 : 1;

    // 1. Move one step forward
    Position oneStep = {currentPosition.row + direction, currentPosition.col};
    if (board.isValidPosition(oneStep) && !board.getPieceAt(oneStep)) {
        moves.push_back({currentPosition, oneStep});

        // 2. Move two steps forward (only from starting row)
        if (currentPosition.row == startRow) {
            Position twoSteps = {currentPosition.row + 2 * direction, currentPosition.col};
            if (board.isValidPosition(twoSteps) && !board.getPieceAt(twoSteps)) {
                moves.push_back({currentPosition, twoSteps});
            }
        }
    }

    // 3. Capture diagonally
    Position leftCapture = {currentPosition.row + direction, currentPosition.col - 1};
    if (board.isValidPosition(leftCapture) && board.getPieceAt(leftCapture) && board.getPieceAt(leftCapture)->getColor() != color) {
        moves.push_back({currentPosition, leftCapture});
    }
    Position rightCapture = {currentPosition.row + direction, currentPosition.col + 1};
    if (board.isValidPosition(rightCapture) && board.getPieceAt(rightCapture) && board.getPieceAt(rightCapture)->getColor() != color) {
        moves.push_back({currentPosition, rightCapture});
    }

    return moves;
}

// Helper function for sliding pieces (Rook, Bishop, Queen)
void addSlidingMoves(vector<Move>& moves, Position start, int dRow, int dCol, const Board& board, PieceColor color) {
    Position current = start;
    while (true) {
        current.row += dRow;
        current.col += dCol;
        if (!board.isValidPosition(current)) break; // Off the board
        
        const auto& piece = board.getPieceAt(current);
        if (piece) { // If there's a piece on the square
            if (piece->getColor() != color) {
                moves.push_back({start, current}); // It's an enemy piece, can capture
            }
            break; // Stop, can't move further whether it's friend or foe
        } else {
            moves.push_back({start, current}); // It's an empty square, can move here
        }
    }
}

vector<Move> Rook::getPossibleMoves(Position currentPosition, const Board& board) const {
    vector<Move> moves;
    addSlidingMoves(moves, currentPosition, 1, 0, board, color);   // Down
    addSlidingMoves(moves, currentPosition, -1, 0, board, color);  // Up
    addSlidingMoves(moves, currentPosition, 0, 1, board, color);   // Right
    addSlidingMoves(moves, currentPosition, 0, -1, board, color);  // Left
    return moves;
}

vector<Move> Knight::getPossibleMoves(Position currentPosition, const Board& board) const {
    vector<Move> moves;
    int dRow[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dCol[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int i = 0; i < 8; ++i) {
        Position target = {currentPosition.row + dRow[i], currentPosition.col + dCol[i]};
        if (board.isValidPosition(target)) {
            const auto& piece = board.getPieceAt(target);
            // Can move if the square is empty or has an enemy piece
            if (!piece || piece->getColor() != color) {
                moves.push_back({currentPosition, target});
            }
        }
    }
    return moves;
}

vector<Move> Bishop::getPossibleMoves(Position currentPosition, const Board& board) const {
    vector<Move> moves;
    addSlidingMoves(moves, currentPosition, 1, 1, board, color);   // Down-Right
    addSlidingMoves(moves, currentPosition, 1, -1, board, color);  // Down-Left
    addSlidingMoves(moves, currentPosition, -1, 1, board, color);  // Up-Right
    addSlidingMoves(moves, currentPosition, -1, -1, board, color); // Up-Left
    return moves;
}

vector<Move> Queen::getPossibleMoves(Position currentPosition, const Board& board) const {
    // A queen's moves are the combination of a rook's and a bishop's moves
    vector<Move> moves;
    // Rook-like moves
    addSlidingMoves(moves, currentPosition, 1, 0, board, color);
    addSlidingMoves(moves, currentPosition, -1, 0, board, color);
    addSlidingMoves(moves, currentPosition, 0, 1, board, color);
    addSlidingMoves(moves, currentPosition, 0, -1, board, color);
    // Bishop-like moves
    addSlidingMoves(moves, currentPosition, 1, 1, board, color);
    addSlidingMoves(moves, currentPosition, 1, -1, board, color);
    addSlidingMoves(moves, currentPosition, -1, 1, board, color);
    addSlidingMoves(moves, currentPosition, -1, -1, board, color);
    return moves;
}

vector<Move> King::getPossibleMoves(Position currentPosition, const Board& board) const {
    vector<Move> moves;
    for (int dRow = -1; dRow <= 1; ++dRow) {
        for (int dCol = -1; dCol <= 1; ++dCol) {
            if (dRow == 0 && dCol == 0) continue; // Skip the square the king is on

            Position target = {currentPosition.row + dRow, currentPosition.col + dCol};
            if (board.isValidPosition(target)) {
                 const auto& piece = board.getPieceAt(target);
                // Can move if the square is empty or has an enemy piece
                if (!piece || piece->getColor() != color) {
                    moves.push_back({currentPosition, target});
                }
            }
        }
    }
    return moves;
}

