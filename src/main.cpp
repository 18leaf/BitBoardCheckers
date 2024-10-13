#include <iostream>
#include "game/Move.h"
#include "game/Player.h"
#include "game/CheckersGame.h"


int main() {
	Game::CheckersGame game("Lindsey", "NOTME");
	game.startGame();
    return 0;
}
