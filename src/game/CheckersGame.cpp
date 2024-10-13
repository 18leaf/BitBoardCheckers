//
// Created by Lindsey on 9/26/2024.
//

#include "CheckersGame.h"

#include <iostream>

#include "exceptions/InvalidMoveException.h"


using namespace Game;
using namespace Exceptions;

CheckersGame::CheckersGame(const std::string &player1Name, const std::string &player2Name) {
	player1 = std::make_unique<Player>(player1Name, true);
	player2 = std::make_unique<Player>(player2Name, false);
	currentPlayer = player1.get();
	board.initializeBoard();
}

void CheckersGame::startGame() {
    // Game loop
    do {
        displayGameStatus();

        try {
            // Get and process player move
            Move move = getPlayerMove();

            // Validate and process move
            validateMove(move);
            processMove(move);

            // Switch to the next player
            switchPlayer();
        } catch (const InvalidMoveException &e) {
            std::cout << "Invalid move: " << e.what() << "\nPlease try again.\n";
        } catch (const std::exception &e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    } while (!isGameOver());

	displayGameStatus();

    // end of game
    std::cout << "Game Over\n";
    std::cout << currentPlayer->getName() << " has no legal moves or pieces left.\n";
    std::cout << (currentPlayer == player1.get() ? player2->getName() : player1->getName()) << " wins!\n";
}

void CheckersGame::switchPlayer() {
    currentPlayer = (currentPlayer == player1.get()) ? player2.get() : player1.get();
}

void CheckersGame::processMove(const Move& move) {
    int startPosition = move.getStartPosition();
    int endPosition = move.getEndPosition();
    bool isPlayerOne = currentPlayer->isPlayerOne();

    // Move the piece on the board
    board.movePiece(startPosition, endPosition, isPlayerOne);
}

bool CheckersGame::isGameOver() const {
    // any legal moves ie has any pieces or is stuck
    return !board.hasAnyLegalMoves(currentPlayer->isPlayerOne());;
}

void CheckersGame::displayGameStatus() const {
    std::cout << "\nCurrent Board:\n";
    board.displayBoard();
    std::cout << currentPlayer->getName() << "'s turn.\n";
}

Move CheckersGame::getPlayerMove() {
    std::string startCoord, endCoord;
    std::cout << "Enter your move (e.g., E3 F4): ";
    std::cin >> startCoord >> endCoord;

    try {
        int startPosition = Game::Board::coordinateToPosition(startCoord);
        int endPosition = Game::Board::coordinateToPosition(endCoord);
        return {startPosition, endPosition};
    } catch (const std::exception &e) {
        throw InvalidMoveException("Invalid input coordinates.");
    }
}

void CheckersGame::validateMove(const Move &move) {
    bool isPlayerOne = currentPlayer->isPlayerOne();
	// is legal move
    if (!board.isLegalMove(move.getStartPosition(), move.getEndPosition(), isPlayerOne)) {
        throw InvalidMoveException("The move is not legal.");
    }
}