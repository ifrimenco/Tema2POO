#include "XorShift.h"

#include <fstream>


XorShift::XorShift(int Seed) :
    _Seed(Seed) {}

int XorShift :: GetRandomNumber(unsigned Low, unsigned High) {
    _Seed ^= _Seed << 13;
	_Seed ^= _Seed >> 17;
	_Seed ^= _Seed << 5;
	int Result = Low + _Seed % (High - Low + 1);
	return Result;
}

int XorShift :: GetRandomNumber() {
    _Seed ^= _Seed << 13;
	_Seed ^= _Seed >> 17;
	_Seed ^= _Seed << 5;
	return _Seed;
}


