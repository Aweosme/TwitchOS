#include "math.h"

double pow(double base, double exp) {
	for(int i = 0; i < exp; i++)
		base *= base;
	return base;
}

double log(double x) {
	return logbase(E, x);
}

double log10(double x) {
	return logbase(10, x);
}

double logbase(double base, double x) {
	//TODO: Add logarithm support
	return x;
}

double sin(double x) {
	//TODO: Add sine support
	return x;
}

double cos(double x) {
	//TODO: Add cosine support
	return x;
}

double tan(double x) {
	//TODO: Add tangent support
	return x;
}

double max(double x, double y) {
	return x > y ? x : y;
}

double min(double x, double y) {
	return x < y ? x : y;
}

double ceil(double x) {
	//TODO: Add ceiling support. It's gonna rain and we won't be protected.
	return x;
}

double floor(double x) {
	//TODO: Add floor support. The dirt under all my furniture is unpleasant.
	return x;
}
