#include <ctime>
#include "Randinator.h"

std::mt19937 Randinator::seed((unsigned int)time(0));

int Randinator::iNum(int low, int high) {
	std::uniform_int_distribution<int> spread(low, high);
	return spread(seed);
}

float Randinator::fNum(float low, float high) {
	std::uniform_real_distribution<float> spread(low, high);
	return spread(seed);
}