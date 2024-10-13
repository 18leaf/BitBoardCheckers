//
// Created by Lindsey on 9/26/2024.
//

#include "Board.h"

#include <iostream>

#include "exceptions/InvalidMoveException.h"
#include "utils/BitManipulationUtility.h"


using namespace Utils;
using namespace Game;
using namespace Exceptions;


// defining constants/ bitmasks for edges of boards and moves
constexpr uint64_t LEFT_EDGE = 0xFEFEFEFEFEFEFEFEULL;
constexpr uint64_t RIGHT_EDGE = 0x7F7F7F7F7F7F7F7FULL;


Board::Board() {
	initializeBoard();
}

void Board::initializeBoard() {
	// init each player and king pieces
	player1Pieces = 0ULL;
	player2Pieces = 0ULL;

	kingPieces = 0ULL;

	// note these were computed using loops below
	player1Pieces = 0xAA55AA;
	player2Pieces = 0x55AA550000000000;
/* loop to compute each players initial pieces
	for (int row = 0; row <= 2; ++row) {
		for (int col = 0; col < 8; ++col) {
			if ((row + col) % 2 == 1) {
				int bitPosition = row * 8 + col;
				player1Pieces = BitManipulationUtility::setBit(player1Pieces, bitPosition);
			}
		}
	}

	// Initialize Player 2 Pieces (Rows 5 to 7)
	for (int row = 5; row <= 7; ++row) {
		for (int col = 0; col < 8; ++col) {
			if ((row + col) % 2 == 1) {
				int bitPosition = row * 8 + col;
				player2Pieces = BitManipulationUtility::setBit(player2Pieces, bitPosition);
			}
		}
	}*/
}

void Board::movePiece(const int startPosition, const int endPosition, const bool isPlayerOne) {
	// validate moves
	if (!isLegalMove(startPosition, endPosition, isPlayerOne)) {
		throw InvalidMoveException("Invalid move");
	}

	const uint64_t startMask = 1ULL << startPosition;
	const uint64_t endMask = 1ULL << endPosition;

	// save capture moves with a possibility mask
	const uint64_t captureMovesFromStart = generateCaptureMoves(startMask, isPlayerOne);

	// Move the piece using the helper function
	movePieceOnBoard(startPosition, endPosition, isPlayerOne);

	// Handle captures using the helper function
	if (captureMovesFromStart & endMask) {
		// get captured piece
		const int jumpedPosition = getJumpedPosition(startPosition, endPosition);

		// Remove the opponent's piece using the helper function
		capturePiece(jumpedPosition, isPlayerOne);
	}

	// Check for promotion to king using the helper function
	if (shouldPromoteToKing(endPosition, isPlayerOne)) {
		promoteToKing(endPosition);
	}
}

void Board::movePieceOnBoard(int startPosition, int endPosition, bool isPlayerOne) {
	uint64_t& playerPieces = isPlayerOne ? player1Pieces : player2Pieces;
	bool isKing = BitManipulationUtility::getBit(kingPieces, startPosition);

	// Move the piece
	playerPieces = BitManipulationUtility::clearBit(playerPieces, startPosition);
	playerPieces = BitManipulationUtility::setBit(playerPieces, endPosition);

	// Update kingPieces
	if (isKing) {
		kingPieces = BitManipulationUtility::clearBit(kingPieces, startPosition);
		kingPieces = BitManipulationUtility::setBit(kingPieces, endPosition);
	}
}

bool Board::shouldPromoteToKing(int position, bool isPlayerOne) {
	int row = position / 8;
	if (isPlayerOne && row == 7) {
		return true;
	} if (!isPlayerOne && row == 0) {
		return true;
	}
	return false;
}

int Board::getJumpedPosition(int startPosition, int endPosition) {
	int startRow = startPosition / 8;
	int startCol = startPosition % 8;
	int endRow = endPosition / 8;
	int endCol = endPosition % 8;

	int jumpedRow = (startRow + endRow) / 2;
	int jumpedCol = (startCol + endCol) / 2;

	return jumpedRow * 8 + jumpedCol;
}

void Board::capturePiece(int position, bool isPlayerOne) {
	// set opponents pieces to opposite pieces of isPlayerOne bool
	uint64_t& opponentPieces = isPlayerOne ? player2Pieces : player1Pieces;

	// is opponenet piece on position
	if (BitManipulationUtility::getBit(opponentPieces, position)) {
		opponentPieces = BitManipulationUtility::clearBit(opponentPieces, position);

		// check if king
		if (BitManipulationUtility::getBit(kingPieces, position)) {
			kingPieces = BitManipulationUtility::clearBit(kingPieces, position);
		}
	} else {
		throw InvalidMoveException("No opponent to capture");
	}
}

void Board::promoteToKing(int position) {
	// To be implemented
	kingPieces = BitManipulationUtility::setBit(kingPieces, position);
}

bool Board::isLegalMove(const int startPosition, const int endPosition, const bool isPlayerOne) {
	// TODO add logic to translate this to user easier ie Coord Based to start position in another function
	if (startPosition < 0 || startPosition >= 64 || endPosition < 0 || endPosition >= 64) {
		return false;
	}

	uint64_t startMask = 1ULL << startPosition;
	uint64_t endMask = 1ULL << endPosition;

	// current player has piece at current start position?
	uint64_t& playerPieces = isPlayerOne ? player1Pieces : player2Pieces;
	if (!(playerPieces & startMask)) {
		return false;
	}

	// no current functionality, but can be used for move suggestions later on future updates
	uint64_t singleStepMoves = generateSingleStepMoves(playerPieces, isPlayerOne);
	uint64_t captureMoves = generateCaptureMoves(playerPieces, isPlayerOne);

	// all moves (can be used for later) show suggestions
	//uint64_t allLegalMoves = singleStepMoves | captureMoves;

	// set to isLegal False
	bool isLegal = false;

	// set startmask to chosen startposition to binary for current piece
	uint64_t pieceMask = startMask;

	// generate all posible single step moves from given start position
	uint64_t singleMovesFromStart = generateSingleStepMoves(pieceMask, isPlayerOne);
	if (singleMovesFromStart & endMask) {
		isLegal = true;
	}

	// generate all possible captures
	uint64_t captureMovesFromStart = generateCaptureMoves(pieceMask, isPlayerOne);
	if (captureMovesFromStart & endMask) {
		isLegal = true;
	}

	return isLegal;
}

uint64_t Board::generateSingleStepMoves(const uint64_t pieces, const bool isPlayerOne) const {
	uint64_t emptySquares = ~(player1Pieces | player2Pieces);
	uint64_t singleMoves = 0ULL;
	// TODO King pieces
	uint64_t kings = kingPieces & pieces;
	uint64_t nonKings = pieces & ~kingPieces;

	// kings can move in all direction
	singleMoves |= ((kings & LEFT_EDGE) << 7) & emptySquares;
	singleMoves |= ((kings & RIGHT_EDGE) << 9) & emptySquares;
	singleMoves |= ((kings & RIGHT_EDGE) >> 7) & emptySquares;
	singleMoves |= ((kings & LEFT_EDGE) >> 9) & emptySquares;



	// shift all pieces in O(1) time checking where possible to shift that doesn't violate masks
	if (isPlayerOne) {
		// shift entire board of pieces North east Where possible IE not interfering with mask
		// note nonKings prevents double moving for kings
		singleMoves |= ((nonKings & LEFT_EDGE) << 7) & emptySquares;
		// north-west
		singleMoves |= ((nonKings & RIGHT_EDGE) << 9) & emptySquares;
	} else {
		// se
		singleMoves |= ((nonKings & LEFT_EDGE) >> 9) & emptySquares;
		// sw
		singleMoves |= ((nonKings & RIGHT_EDGE) >> 7) & emptySquares;
	}
	// a mask of possible moves
	return singleMoves;
}

uint64_t Board::generateCaptureMoves(const uint64_t pieces, const bool isPlayerOne) const {
	uint64_t emptySquares = ~(player1Pieces | player2Pieces);
	uint64_t opponentPieces = isPlayerOne ? player2Pieces : player1Pieces;
	uint64_t captures = 0ULL;

	// king pieces functionality
	uint64_t kings = kingPieces & pieces; // ensure kings are players kings
	uint64_t nonKings = pieces & ~kingPieces;

	// all directions for kings to capture for each direction
	uint64_t potential = ((kings & LEFT_EDGE) << 7) & opponentPieces; // holds potential moves for kings
	captures |= ((potential & LEFT_EDGE) << 7) & emptySquares;

	potential = ((kings & RIGHT_EDGE) << 9) & opponentPieces;
	captures |= ((potential & RIGHT_EDGE) << 9) & emptySquares;

	potential = ((kings & RIGHT_EDGE) >> 7) & opponentPieces;
	captures |= ((potential & RIGHT_EDGE) >> 7) & emptySquares;

	potential = ((kings & LEFT_EDGE) >> 9) & opponentPieces;
	captures |= ((potential & LEFT_EDGE) >> 9) & emptySquares;
	// for captures... check diagonal if populated, then one more shift in same direction = a capture
	// if potential is true/1 then if diagonal of potential is empty it is capturable
	/*
	 * 000
	 * 0X0
	 * 00R
	 *
	 * NW of red is X, but NW of X is empty, therefore R can capture X
	 */
	if (isPlayerOne) {
		// ne cap
		potential = ((nonKings & LEFT_EDGE) << 7) & opponentPieces;
		captures |= ((potential & LEFT_EDGE) << 7) & emptySquares;
		// nw cap
		potential = ((nonKings & RIGHT_EDGE) << 9) & opponentPieces;
		captures |= ((potential & RIGHT_EDGE) << 9) & emptySquares;
	} else {
		// same but for other player se
		potential = ((nonKings & LEFT_EDGE) >> 9) & opponentPieces;
		captures |= ((potential & LEFT_EDGE) >> 9) & emptySquares;
		// sw
		potential = ((nonKings & RIGHT_EDGE) >> 7) & opponentPieces;
		captures |= ((potential & RIGHT_EDGE) >> 7) & emptySquares;
	}

	return captures;
}

bool Board::hasAnyLegalMoves(bool isPlayerOne) const {
	uint64_t playerPieces = isPlayerOne ? player1Pieces : player2Pieces;

	// generate a 64bit string... if == 0....0 then no moves remain, either no pieces or no legal moves
	uint64_t singleMoves = generateSingleStepMoves(playerPieces, isPlayerOne);
	uint64_t captureMoves = generateCaptureMoves(playerPieces, isPlayerOne);

	// return all valid moves possible by player x
	return (singleMoves != 0ULL) || (captureMoves != 0ULL);
}


int Board::coordinateToPosition(const std::string &coord) {
	if (coord.length() != 2) {
		throw std::invalid_argument("Invalid coordinate length.");
	}

	char colChar = coord[0];
	char rowChar = coord[1];

	// Convert column character to column index (0-7)
	int colIndex;
	if (colChar >= 'A' && colChar <= 'H') {
		colIndex = colChar - 'A';
	} else if (colChar >= 'a' && colChar <= 'h') {
		colIndex = colChar - 'a';
	} else {
		throw std::invalid_argument("Invalid column character.");
	}

	// Convert row character to row index (0-7)
	int rowIndex;
	if (rowChar >= '1' && rowChar <= '8') {
		rowIndex = rowChar - '1'; // Rows are numbered from bottom (1) to top (8)
	} else {
		throw std::invalid_argument("Invalid row character.");
	}

	// Calculate bit position
	int bitPosition = rowIndex * 8 + colIndex;

	// Validate bit position is within bounds (0-63)
	if (bitPosition < 0 || bitPosition >= 64) {
		throw std::out_of_range("Bit position out of range.");
	}

	return bitPosition;
}


uint64_t Board::getPlayer1Pieces() const {
	return player1Pieces;
}

uint64_t Board::getPlayer2Pieces() const {
	return player2Pieces;
}

uint64_t Board::getKingPieces() const {
	return kingPieces;
}

// Setter methods for testing
void Board::setPlayer1Pieces(const uint64_t pieces) {
	player1Pieces = pieces;
}

void Board::setPlayer2Pieces(const uint64_t pieces) {
	player2Pieces = pieces;
}

void Board::setKingPieces(const uint64_t pieces) {
	kingPieces = pieces;
}


void Board::displayBoard() const {
	std::cout << "  A B C D E F G H\n";
	for (int row = 7; row >= 0; --row) {
		std::cout << row + 1 << " ";
		for (int col = 0; col < 8; ++col) {
			int bitPosition = row * 8 + col;
			char pieceChar = ' ';
			if ((row + col) % 2 == 1) {
				if (BitManipulationUtility::getBit(player1Pieces, bitPosition)) {
					if (BitManipulationUtility::getBit(kingPieces, bitPosition)) {
						pieceChar = 'W'; // p1 king
					} else {
						pieceChar = 'w'; // p2 king
					}
				} else if (BitManipulationUtility::getBit(player2Pieces, bitPosition)) {
					if (BitManipulationUtility::getBit(kingPieces, bitPosition)) {
						pieceChar = 'B';
					} else {
						pieceChar = 'b';
					}
				} else {
					pieceChar = '.'; // playalbe square
				}
			} else {
				// Non-playable square
				pieceChar = ' ';
			}
			std::cout << pieceChar << " ";
		}
		std::cout << row + 1 << "\n";
	}
	std::cout << "  A B C D E F G H\nPlayer 1 Pieces: ";
	std::cout << BitManipulationUtility::toBinaryString(player1Pieces) << "\nPlayer 2 Pieces: "<< BitManipulationUtility::toBinaryString(player2Pieces) << "\n";
	std::cout << "Player 1 Pieces: " << BitManipulationUtility::toHexString(player1Pieces) << "\nPlayer 2 Pieces: " << BitManipulationUtility::toHexString(player2Pieces) << "\n";
}
