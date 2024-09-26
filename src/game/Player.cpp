//
// Created by Lindsey on 9/26/2024.
//

#include "Player.h"


using namespace Game;

Player::Player(const std::string& name, bool isPlayerOne)
	: playerName(name), playerOne(isPlayerOne) {
}

std::string Player::getName() const {
	return playerName;
}

bool Player::isPlayerOne() const {
	return playerOne;
}

void Player::setName(const std::string& name) {
	playerName = name;
}