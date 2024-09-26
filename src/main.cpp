#include <iostream>
#include "game/Move.h"
#include "game/Player.h"
#include "game/CheckersGame.h"

using namespace Game;

int main() {
	CheckersGame game("Lindsey", "None");
	game.startGame();
    return 0;
}
