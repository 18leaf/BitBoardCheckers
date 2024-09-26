//
// Created by Lindsey on 9/26/2024.
//

#include "BitManipulationUtility.h"

namespace Utils
{
	uint64_t BitManipulationUtility::setBits(uint64_t value, int position) {
		return value | (1ULL << position);
	}

}