//
// Created by Lindsey on 9/26/2024.
//

#include "Board.h"
#include "utils/BitManipulationUtility.h"


using namespace Utils;
using namespace Game;


Board::Board() {
	initializeBoard();
}

void Board::initializeBoard() {
	// init each player and king pieces
	player1Pieces = 0x00000FFFULL;         // first 12 positions
	player2Pieces = 0xFFF0000000000000ULL; // last 12 positions
	kingPieces = 0ULL; // null
}

void Board::movePiece(int startPosition, int endPosition, bool isPlayerOne) {
	// To be implemented
}

void Board::capturePiece(int position, bool isPlayerOne) {
	// To be implemented
}

void Board::promoteToKing(int position) {
	// To be implemented
}

void Board::displayBoard() {
	// To be implemented
}

bool Board::isLegalMove(int startPosition, int endPosition, bool isPlayerOne) {
	// To be implemented
	return false;
}

// Optional helper methods
void Board::setPiece(uint64_t& bitboard, int position) {
	bitboard = BitManipulationUtility::setBit(bitboard, position);
}

void Board::clearPiece(uint64_t& bitboard, int position) {
	bitboard = BitManipulationUtility::clearBit(bitboard, position);
}

