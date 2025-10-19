#ifndef MOVE_H
#define MOVE_H


struct Position {
    int row;
    int col;

    // Overload the == operator to easily compare two positions
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
};

// Represents a move from a start position to an end position
struct Move {
    Position start;
    Position end;
};

#endif // MOVE_H
