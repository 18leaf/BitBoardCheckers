//
// Created by Lindsey on 9/26/2024.
//

#include "Move.h"

using namespace Game;

Move::Move(int start, int end, bool isCapture)
	: startPosition(start), endPosition(end), isCaptureMove(isCapture){
}

int Move::getStartPosition() const {
	return startPosition;
}

int Move::getEndPosition() const {
	return endPosition;
}

bool Move::getIsCapture() const {
	return isCaptureMove;
}

void Move::setStartPosition(int start) {
	startPosition = start;
}

void Move::setEndPosition(int end) {
	endPosition = end;
}

void Move::setIsCapture(bool isCapture) {
	isCaptureMove = isCapture;
}