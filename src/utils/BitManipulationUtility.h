//
// Created by Lindsey on 9/26/2024.
//

#ifndef BITMANIPULATIONUTILITY_H
#define BITMANIPULATIONUTILITY_H
#include <cstdint>
#include <string>


namespace Utils {

class BitManipulationUtility {
public:
	// Bit maniputlation methods
    static uint64_t setBit(uint64_t value, int position);
	static uint64_t clearBit(uint64_t value, int position);
	static uint64_t toggleBit(uint64_t value, int position);
	static int getBit(uint64_t value, int position);

	// Binary Arithmetic
	static uint64_t bitAdd(uint64_t a, uint64_t b);
	static uint64_t bitSubtract(uint64_t a, uint64_t b);
	static uint64_t bitMultiply(uint64_t a, uint64_t b);
	static uint64_t bitDivide(uint64_t a, uint64_t b);

	// convert to strings binary/hex
	static std::string toBinaryString(uint64_t value);
	static std::string toHexString(uint64_t value);
};

}

#endif //BITMANIPULATIONUTILITY_H
