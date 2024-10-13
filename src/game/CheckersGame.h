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
	Board board;
	void validateMove(const Move& move);
	[[nodiscard]] bool isGameOver() const;

private:
	// unique players initialization
	std::unique_ptr<Player> player1;
	std::unique_ptr<Player> player2;
	// contents of player... either player 1 or 2
	Player* currentPlayer;

	// game state methods
	void switchPlayer();
	void processMove(const Move& move);
	void displayGameStatus() const;
	// helpers
	static Move getPlayerMove();

};

}

#endif //CHECKERSGAME_H
