#ifndef COMPILER_WHYINFO_H_
#define COMPILER_WHYINFO_H_

#include <set>
#include <string>

#include "options.h"

// #define REGISTER_PRESSURE 4

namespace LL2W {
	/** Contains constants pertaining to the Why.js architecture. */
	struct WhyInfo {
		constexpr static int wordSize = 8; // in bytes
		constexpr static int totalRegisters = 128;

		constexpr static int returnValueOffset = 7, returnValueCount = 16;
		constexpr static int    argumentOffset = 23,   argumentCount = 16;
		constexpr static int   temporaryOffset = 39,  temporaryCount = 23;
		constexpr static int       savedOffset = 62,      savedCount = 23;
		constexpr static int      kernelOffset = 85,     kernelCount = 16;
		constexpr static int   assemblerOffset = 102, assemblerCount = 16;
		constexpr static int    floatingOffset = 118,  floatingCount = 4;
		constexpr static int   exceptionOffset = 122, exceptionCount = 6;

		constexpr static int zeroOffset = 0,
		        globalAreaPointerOffset = 1,
		             stackPointerOffset = 2,
		             framePointerOffset = 3,
		            returnAddressOffset = 4,
		                       loOffset = 5,
		                       hiOffset = 6,
		                   statusOffset = 101;

		constexpr static int halfFloatWidth = 4, floatWidth = 8, doubleWidth = 8, pointerWidth = 8; // in bytes

		constexpr static int generalPurposeRegisters = temporaryCount + savedCount;
#ifdef REGISTER_PRESSURE
		constexpr static int allocatableRegisters = REGISTER_PRESSURE;
#else
		constexpr static int allocatableRegisters = generalPurposeRegisters;
#endif
		static std::set<int> makeRegisterPool();
		static bool isSpecialPurpose(int);
		static bool isArgumentRegister(int);
		static std::string registerName(int);
	};
}

#endif
