//
// Created by Lindsey on 9/26/2024.
//

#ifndef MOVE_H
#define MOVE_H


namespace Game
{


class Move {
public:
	Move(int start, int end, bool isCapture = false);

	// getters
	int getStartPosition() const;
	int getEndPosition() const;
	bool getIsCapture() const;

	// setters
	void setStartPosition(int start);
	void setEndPosition(int end);
	void setIsCapture(bool isCapture);

private:
	int startPosition;
	int endPosition;
	bool isCaptureMove;
};


}

#endif //MOVE_H
