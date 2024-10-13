//
// Created by Lindsey on 10/13/2024.
//


#include <iostream>
#include <cassert>

#include "game/CheckersGame.h"
#include "game/Move.h"
#include "exceptions/InvalidMoveException.h"
#include "game/Board.h"
#include "utils/BitManipulationUtility.h"

using namespace Game;
using namespace Utils;

// Include BitManipulationUtility if not already included

void testBoardInitialization() {
    Board board;
    board.initializeBoard();

    uint64_t player1Pieces = board.getPlayer1Pieces();
    uint64_t player2Pieces = board.getPlayer2Pieces();

    // Test initial positions for Player 1
    for (int row = 0; row <= 2; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 == 1) {
                int bitPosition = row * 8 + col;
                assert(BitManipulationUtility::getBit(player1Pieces, bitPosition));
            }
        }
    }

    // Test initial positions for Player 2
    for (int row = 5; row <= 7; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 == 1) {
                int bitPosition = row * 8 + col;
                assert(BitManipulationUtility::getBit(player2Pieces, bitPosition));
            }
        }
    }

    std::cout << "Board initialization test passed.\n";
}

void testLegalMove() {
    Board board;
    board.initializeBoard();

    // Move a piece from E3 to D4 for Player 1
    int startPosition = Game::Board::coordinateToPosition("E3");
    int endPosition = Game::Board::coordinateToPosition("D4");

    assert(board.isLegalMove(startPosition, endPosition, true));

    // Perform the move
    board.movePiece(startPosition, endPosition, true);

    uint64_t player1Pieces = board.getPlayer1Pieces();

    // Check that the piece has moved
    assert(!BitManipulationUtility::getBit(player1Pieces, startPosition));
    assert(BitManipulationUtility::getBit(player1Pieces, endPosition));

    std::cout << "Legal move test passed.\n";
}

void testIllegalMove() {
    Board board;
    board.initializeBoard();

    // Attempt to move a piece from E3 to E4 (which is illegal in checkers)
    int startPosition = Game::Board::coordinateToPosition("E3");
    int endPosition = Game::Board::coordinateToPosition("E4");

    assert(!board.isLegalMove(startPosition, endPosition, true));

    try {
        board.movePiece(startPosition, endPosition, true);
        assert(false); // Should not reach here
    } catch (const Exceptions::InvalidMoveException& e) {
        std::cout << "Caught expected InvalidMoveException: " << e.what() << "\n";
    }

    std::cout << "Illegal move test passed.\n";
}

void testCaptureMove() {
    Board board;
    board.initializeBoard();

    // Set up a scenario where Player 1 can capture a Player 2 piece
    // Move Player 1 piece from E3 to D4
    board.movePiece(
        Game::Board::coordinateToPosition("E3"),
        Game::Board::coordinateToPosition("D4"),
        true
    );

    // Move Player 2 piece from D6 to E5
    board.movePiece(
        Game::Board::coordinateToPosition("D6"),
        Game::Board::coordinateToPosition("E5"),
        false
    );

    // Player 1 captures the piece at E5 by moving from D4 to F6
    int startPosition = Game::Board::coordinateToPosition("D4");
    int endPosition = Game::Board::coordinateToPosition("F6");

    assert(board.isLegalMove(startPosition, endPosition, true));

    // Perform the capture
    board.movePiece(startPosition, endPosition, true);

    // Verify that the opponent's piece was captured
    int capturedPosition = Game::Board::coordinateToPosition("E5");
    uint64_t player2Pieces = board.getPlayer2Pieces();
    assert(!BitManipulationUtility::getBit(player2Pieces, capturedPosition));

    std::cout << "Capture move test passed.\n";
}

void testPromotionToKing() {
    Board board;
    board.initializeBoard();

    // Manually set a piece near promotion
    int startPosition = Game::Board::coordinateToPosition("D6");
    int endPosition = Game::Board::coordinateToPosition("E7");

    // Clear initial pieces
    board.setPlayer1Pieces(0ULL);
    board.setPlayer2Pieces(0ULL);
    board.setKingPieces(0ULL);

    // Place a Player 1 piece at D6
    uint64_t player1Pieces = BitManipulationUtility::setBit(0ULL, startPosition);
    board.setPlayer1Pieces(player1Pieces);

    // Move to E7
    board.movePiece(startPosition, endPosition, true);

    // Now move to promotion row
    int promotionPosition = Game::Board::coordinateToPosition("F8");
    board.movePiece(endPosition, promotionPosition, true);

    uint64_t kingPieces = board.getKingPieces();

    // Verify that the piece is now a king
    assert(BitManipulationUtility::getBit(kingPieces, promotionPosition));

    std::cout << "Promotion to king test passed.\n";
}

void testHasAnyLegalMoves() {
    Board board;
    board.initializeBoard();

    // Assume it's Player 1's turn
    assert(board.hasAnyLegalMoves(true));

    // Manually remove all Player 1 pieces
    board.setPlayer1Pieces(0ULL);

    // Now Player 1 should have no legal moves
    assert(!board.hasAnyLegalMoves(true));

    std::cout << "Has any legal moves test passed.\n";
}

void testGameOverCondition() {
	CheckersGame game("Alice", "Bob");


	// Manually remove all pieces of the current player (Player 2)
	game.board.setPlayer1Pieces(0ULL);

	// Check if the game correctly identifies game over
	assert(game.isGameOver());

	std::cout << "Game over condition test passed.\n";
}


void testValidateMove() {
	CheckersGame game("Alice", "Bob");

	// Valid move
	Move validMove(
		Game::Board::coordinateToPosition("E3"),
		Game::Board::coordinateToPosition("D4")
	);

	try {
		game.validateMove(validMove);
		std::cout << "Valid move test passed.\n";
	} catch (const Exceptions::InvalidMoveException& e) {
		assert(false); // Should not throw
	}

	// Invalid move
	Move invalidMove(
		Game::Board::coordinateToPosition("E3"),
		Game::Board::coordinateToPosition("E4")
	);

	try {
		game.validateMove(invalidMove);
		assert(false); // Should throw
	} catch (const Exceptions::InvalidMoveException& e) {
		std::cout << "Caught expected InvalidMoveException for invalid move: " << e.what() << "\n";
	}
}

int main() {
    testBoardInitialization();
    testLegalMove();
    testIllegalMove();
    testCaptureMove();
    testPromotionToKing();
    testHasAnyLegalMoves();
    testGameOverCondition();
    testValidateMove();

    std::cout << "All tests passed successfully.\n";
    return 0;
}
