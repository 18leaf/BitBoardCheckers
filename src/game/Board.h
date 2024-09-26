//
// Created by Lindsey on 9/26/2024.
//

#ifndef BOARD_H
#define BOARD_H
#include <cstdint>

namespace Game
{

class Board {
public:
	Board();

	void initializeBoard();

	// methods for board state
	void movePiece(int startPosition, int endPosition, bool isPlayerOne);
	void capturePiece(int position, bool isPlayerOne);
	void promoteToKing(int position);

	// display board
	void displayBoard();

	// check move legality
	bool isLegalMove(int startPosition, int endPosition, bool isPlayerOne);

private:
	// holds pieces for each player and kings
	uint64_t player1Pieces{};
	uint64_t player2Pieces{};
	uint64_t kingPieces{};

	// helpers for pieces through board
	void setPiece(uint64_t& bitboard, int position);
	void clearPiece(uint64_t& bitboard, int position);
};

}

#endif //BOARD_H
