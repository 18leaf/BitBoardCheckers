//
// Created by Lindsey on 9/26/2024.
//

#include "CheckersGame.h"

#include <iostream>


using namespace Game;

CheckersGame::CheckersGame(const std::string &player1Name, const std::string &player2Name) {
	player1 = std::make_unique<Player>(player1Name, true);
	player2 = std::make_unique<Player>(player2Name, false);
	currentPlayer = player1.get();
	board.initializeBoard();
}


void CheckersGame::startGame() {
	// TODO implement Move Stack to track moves previously made
	// game loop
	while (!isGameOver()) {
		displayGameStatus();

		// try to make new move, check validatiy, process, switch player, else reprompt
		if (Move move = getPlayerMove(); validateMove(move)) {
			processMove(move);
			switchPlayer();
		} else {
			// TODO THROW EXCEPTION AND HANDLE
			std::cout << "Invalid Move. Try Again" << std::endl;
		}
	}

	// TODO implement end of Game prompt
	std::cout << "Game Over" << std::endl;
	if (currentPlayer == player1.get()) {
		std::cout << player2->getName() << " wins!\n";
	} else {
		std::cout << player1->getName() << " wins!\n";
	}
}

void CheckersGame::switchPlayer() {
	if (currentPlayer == player1.get()) {
		currentPlayer = player2.get();
	} else {
		currentPlayer = player1.get();
	}
}

bool CheckersGame::processMove(const Move& move) {
	// apply move to the board
	const int startPosition = move.getStartPosition();
	const int endPosition = move.getEndPosition();
	const bool isPlayerOne = currentPlayer->isPlayerOne();
	board.movePiece(startPosition, endPosition, isPlayerOne);

	// handle captures
	if (move.getIsCapture()) {
		const int capturedPosition = (startPosition + endPosition) / 2;
		board.capturePiece(capturedPosition, isPlayerOne);
	}

	// check king promotion
	board.promoteToKing(endPosition);

	return true;
}

bool CheckersGame::isGameOver() {
	// todo implement logic
	return false;
}

void CheckersGame::displayGameStatus() {
	std::cout << "\nCurrent Board:\n";
	board.displayBoard();
	std::cout << currentPlayer->getName() << "'s turn.\n";
}

Move CheckersGame::getPlayerMove() {
	int start, end;
	std::cout << "Enter your move (start end): ";
	std::cin >> start >> end;

	// TODO CHECK IF CAPTURED

	return {start, end};
}

bool CheckersGame::validateMove(const Move &move) {
	bool isPlayerOne = currentPlayer->isPlayerOne();
	return board.isLegalMove(move.getStartPosition(), move.getEndPosition(), isPlayerOne);
}
