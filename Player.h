#ifndef PLAYER_H
#define PLAYER_H

#include "Move.h"
#include "Board.h" 

class Player {
public:    
    virtual ~Player() = default;

    virtual Move getMove(const Board& board) const = 0;
};

class HumanPlayer : public Player {
public:    
    Move getMove(const Board& board) const override;
};

#endif // PLAYER_H

