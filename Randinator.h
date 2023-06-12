#pragma once
#include <random>

class Randinator
{
	static std::mt19937 seed;
public:
	static int iNum(int, int);
	static float fNum(float, float);
};

