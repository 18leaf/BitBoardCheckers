//
// Created by Lindsey on 9/26/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

namespace Game
{

class Player {
public:
	Player(const std::string& name, bool isPlayerOne);

	// getters
	std::string getName() const;
	bool isPlayerOne() const;

	//setters
	void setName(const std::string& name);
private:
	std::string playerName;
	bool playerOne;
};

}

#endif //PLAYER_H
