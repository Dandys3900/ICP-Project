#ifndef FANCY_MATH_H
#define FANCY_MATH_H


#include <math.h>
#include "vector2.h"


#define PI 3.1415926535897932384626433833
#define E 2.7182818284590452353602874714
#define TAU 6.2831853071795864769252867666
#define TOLERANCE 0.00001f


inline float minf(float f1, float f2) {
	return f1 < f2 ? f1 : f2;
}


inline float max(float f1, float f2) {
	return f1 > f2 ? f1 : f2;
}


inline float clamp(float f, float min, float max) {
	return f < min ? min : (f > max ? max : f);
}


inline bool is_zero_approx(float f) {
	return abs(f) < TOLERANCE;
}


inline bool is_equal_approx(float f1, float f2) {
	float x = max(f1, f2);
	return abs(f1 - x) < TOLERANCE;
}


#endif
