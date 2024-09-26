//
// Created by Lindsey on 9/26/2024.
//

#ifndef CHECKERSGAME_H
#define CHECKERSGAME_H
#include <memory>
#include <string>

#include "Board.h"
#include "Player.h"
#include "Move.h"

namespace Game
{

class CheckersGame {
public:

	CheckersGame(const std::string &player1Name, const std::string &player2Name);

	// initialize loop
	void startGame();

private:
	Board board;
	// unique players initialization
	std::unique_ptr<Player> player1;
	std::unique_ptr<Player> player2;
	// contents of player... either player 1 or 2
	Player* currentPlayer;

	// game state methods
	void switchPlayer();
	bool processMove(const Move& move);
	bool isGameOver();
	void displayGameStatus();

	// helpers
	Move getPlayerMove();
	bool validateMove(const Move& move);
};

}

#endif //CHECKERSGAME_H
