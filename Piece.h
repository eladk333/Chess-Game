#ifndef PIECE_H
#define PIECE_H

#include "Move.h"
#include <vector>


class Board; 


enum class PieceType { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN, EMPTY };
enum class PieceColor { WHITE, BLACK, NONE };


class Piece {
public:
    
    Piece(PieceColor color, PieceType type);
    
    virtual ~Piece() = default;

    virtual std::vector<Move> getPossibleMoves(Position currentPosition, const Board& board) const = 0;

    // Getter functions
    PieceColor getColor() const;
    PieceType getType() const;
    
    // Helper function to get a character representation for the console display
    char getCharRepresentation() const;

protected:    
    PieceColor color;
    PieceType type;
};

class Pawn : public Piece {
public:
    Pawn(PieceColor color);
    std::vector<Move> getPossibleMoves(Position currentPosition, const Board& board) const override;
};

class Rook : public Piece {
public:
    Rook(PieceColor color);
    std::vector<Move> getPossibleMoves(Position currentPosition, const Board& board) const override;
};

class Knight : public Piece {
public:
    Knight(PieceColor color);
    std::vector<Move> getPossibleMoves(Position currentPosition, const Board& board) const override;
};

class Bishop : public Piece {
public:
    Bishop(PieceColor color);
    std::vector<Move> getPossibleMoves(Position currentPosition, const Board& board) const override;
};

class Queen : public Piece {
public:
    Queen(PieceColor color);
    std::vector<Move> getPossibleMoves(Position currentPosition, const Board& board) const override;
};

class King : public Piece {
public:
    King(PieceColor color);
    std::vector<Move> getPossibleMoves(Position currentPosition, const Board& board) const override;
};


#endif // PIECE_H

