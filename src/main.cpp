#include <iostream>
#include "game/Move.h"
#include "game/Player.h"

using namespace Game;

int main() {
	Player player1("Alice", true);
	Player player2("Bob", false);

	std::cout << "Player 1: " << player1.getName() << ", Is Player One: " << (player1.isPlayerOne() ? "Yes" : "No") << std::endl;
	std::cout << "Player 2: " << player2.getName() << ", Is Player One: " << (player2.isPlayerOne() ? "Yes" : "No") << std::endl;

	Move move(12, 16, true);
	std::cout << "Start Position: " << move.getStartPosition() << std::endl;
	std::cout << "End Position: " << move.getEndPosition() << std::endl;
	std::cout << "Is Capture: " << (move.getIsCapture() ? "Yes" : "No") << std::endl;
    return 0;
}
