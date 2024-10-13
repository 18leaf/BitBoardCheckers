//
// Created by Lindsey on 9/26/2024.
//

#ifndef BOARD_H
#define BOARD_H
#include <cstdint>
#include <string>

namespace Game
{

class Board {
public:
	Board();

	void initializeBoard();

	// methods for board state
	void movePiece(int startPosition, int endPosition, bool isPlayerOne);
	// display board
	void displayBoard() const;
	// check move legality
	bool isLegalMove(int startPosition, int endPosition, bool isPlayerOne);
	static int coordinateToPosition(const std::string& coord);
	[[nodiscard]] bool hasAnyLegalMoves(bool isPlayerOne) const;

	// mostly for test cases
	[[nodiscard]] uint64_t getPlayer1Pieces() const;
	[[nodiscard]] uint64_t getPlayer2Pieces() const;
	[[nodiscard]] uint64_t getKingPieces() const;

	// for test cases
	void setPlayer1Pieces(uint64_t pieces);
	void setPlayer2Pieces(uint64_t pieces);
	void setKingPieces(uint64_t pieces);



private:
	void movePieceOnBoard(int startPosition, int endPosition, bool isPlayerOne);
	static bool shouldPromoteToKing(int position, bool isPlayerOne);
	static int getJumpedPosition(int startPosition, int endPosition);
	void promoteToKing(int position);
	void capturePiece(int position, bool isPlayerOne);

	[[nodiscard]] uint64_t generateSingleStepMoves(uint64_t pieces, bool isPlayerOne) const;
	[[nodiscard]] uint64_t generateCaptureMoves(uint64_t pieces, bool isPlayerOne) const;

	uint64_t player1Pieces{};
	uint64_t player2Pieces{};
	uint64_t kingPieces{};
};

}

#endif //BOARD_H
