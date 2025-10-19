#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include <memory>

class Game {
public:
    Game(std::unique_ptr<Player> player1, std::unique_ptr<Player> player2);

    // Main game loop.
    void run();

private:
    Board board;
    std::unique_ptr<Player> whitePlayer;
    std::unique_ptr<Player> blackPlayer;
    Player* currentPlayer; // A raw pointer to the current player
    bool isGameOver;

    // Helper functions
    void switchPlayer();
    bool checkGameOver();
};

#endif // GAME_H

