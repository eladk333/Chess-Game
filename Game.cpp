#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(unique_ptr<Player> player1, unique_ptr<Player> player2)
    : whitePlayer(move(player1)), blackPlayer(move(player2)), isGameOver(false) {
    
    board.setupInitialPosition();
    // White player always starts
    currentPlayer = whitePlayer.get(); 
}

void Game::run() {
    while (!isGameOver) {
        board.display();
        cout << (currentPlayer == whitePlayer.get() ? "White" : "Black") << "'s turn." << endl;

        Move playerMove = currentPlayer->getMove(board);

        // TODO: Add move validation logic here.
        // For now, we'll just execute the move.
        
        board.executeMove(playerMove);

        isGameOver = checkGameOver();
        if (!isGameOver) {
            switchPlayer();
        }
    }
    cout << "Game Over!" << endl;
    // TODO: Announce winner
}

void Game::switchPlayer() {
    if (currentPlayer == whitePlayer.get()) {
        currentPlayer = blackPlayer.get();
    } else {
        currentPlayer = whitePlayer.get();
    }
}

bool Game::checkGameOver() {
    // TODO: Implement actual checkmate/stalemate logic.
    // For now, the game will run indefinitely.
    return false;
}

