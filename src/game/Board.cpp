//
// Created by Lindsey on 9/26/2024.
//

#include "Board.h"

#include "Player.h"
#include "utils/BitManipulationUtility.h"

using namespace Utils;

namespace Game
{
	// all Board methods

	void Board::setPiece(int position, Player player) {
		if (player.isPlayerOne()) {
			player1Pieces = BitManipulationUtility::setBit(player1Pieces, position);
		} else {
			player2Pieces = BitManipulationUtility::setBit(player2Pieces, position);
		}
	}
}
