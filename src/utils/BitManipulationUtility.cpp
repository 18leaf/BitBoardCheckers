//
// Created by Lindsey on 9/26/2024.
//

#include "BitManipulationUtility.h"
#include <bitset>
#include <cmath>
#include <sstream>

using namespace Utils;

uint64_t BitManipulationUtility::setBit(uint64_t value, int position) {
	if (position < 0 || position > 63) {
		throw std::out_of_range("Bit position must be between 0 and 63");
	}
	// shifts the bit 1 to the left by position bits, value | bitwise OR operator to set the bit ON
	return value | (1ULL << position);
}

uint64_t BitManipulationUtility::clearBit(uint64_t value, int position) {
	if (position < 0 || position > 63) {
		throw std::out_of_range("Bit position must be between 0 and 63");
	}
	// bitwise & after masking others to 1 except @ position
	return value & ~(1ULL << position);
}

uint64_t BitManipulationUtility::toggleBit(uint64_t value, int position) {
	if (position < 0 || position > 63) {
		throw std::out_of_range("Bit position must be between 0 and 63");
	}
	// bitwise XOR at position
	return value ^ (1ULL << position);
}

int BitManipulationUtility::getBit(uint64_t value, int position) {
	if (position < 0 || position > 63) {
		throw std::out_of_range("Bit position must be between 0 and 63");
	}
	// shift bit to right by position, get value at position
	return (value >> position) & 1U;
}

uint64_t BitManipulationUtility::bitAdd(uint64_t a, uint64_t b) {
	// loop until b was fully executed onto a, return a after
	while (b != 0) {
		uint64_t t = a & b;
		// XOR a, b (if both are 1 or 0 -> 0) else -> 1
		a = a ^ b;
		// carry shifted
		b = t << 1;
	}
	return a;
}

uint64_t BitManipulationUtility::bitSubtract(uint64_t a, uint64_t b) {
	// loop until b was fully executed onto a, return a after
	while (b != 0) {
		// not a and b
		uint64_t t = (~a) & b;
		// toggle bit
		a = a ^ b;
		// shift carried
		b = t << 1;
	}
	return a;
}

uint64_t BitManipulationUtility::bitMultiply(uint64_t a, uint64_t b) {
	// using Russian Peasant Algorithm ie 12 * 4
	/// 6 | 8   or  000110 | 001000      *** notice the left side shift to right in case would be b-
	/// 3 | 16  or  000011 | 010000      *** effectively multuplying by factor of 2
	/// 1 | 32  or  000001 | 100000
	/// result = 3,1 | 16 + 32 = 48 OR = 110000
	/// Note operates with minimum add operations 12 / 4 = 3 steps Greatest common factor of steps
	uint64_t result = 0;
	// loop down until hits 0
	// multiply a by 2, divide b by factor of 2, Save b when it is odd ie LSB = 1, Add that to result if LSB == 1
	while (b > 0) {
		// LSB = 1
		if (b & 1U) {
			// result = sum of a multiplied by two where b is odd
			result = bitAdd(result, a);
		}
		// perform a shift = a mult by factor of 2
		a <<= 1;
		// perform b shift = b divide by factor of 2, execute until b < 1 == 0
		b >>= 1;

	}
	return result;
}

uint64_t BitManipulationUtility::bitDivide(uint64_t a, uint64_t b) {
	// cannot divide by zero
	// a divided b divisor
	if (b == 0) {
		throw std::overflow_error("Divide by zero");
	}

	uint64_t quotient = 0;
	uint64_t remainder = 0;

	// iterate over every bit
	for (int i = 63; i >= 0; i--) {
		remainder <<= 1;
		// remainder at digit over set to position shifted from left to right each loop and LSB
		remainder |= (a >> i) & 1U;
		if (remainder >= b) {
			remainder = bitSubtract(remainder, b);
			quotient |= (1ULL << i);
		}
	}
	return quotient;
}

std::string BitManipulationUtility::toBinaryString(const uint64_t value) {
	// To be implemented
	const std::bitset<64> bits(value);
	return bits.to_string();
}

std::string BitManipulationUtility::toHexString(uint64_t value) {
	// To be implemented
	std::stringstream ss;
	ss << std::hex << std::uppercase << value;
	return ss.str();
}

