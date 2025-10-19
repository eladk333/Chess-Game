#include "Game.h"
#include "Player.h"
#include <memory>

int main() {
    // Create two human players
    auto player1 = std::make_unique<HumanPlayer>();
    auto player2 = std::make_unique<HumanPlayer>();

    // Create the game instance, giving it ownership of the players
    Game chessGame(std::move(player1), std::move(player2));

    // Start the game loop
    chessGame.run();

    return 0;
}

