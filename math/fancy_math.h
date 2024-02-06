#ifndef FANCY_MATH_H
#define FANCY_MATH_H

#define _USE_MATH_DEFINES
#include <math.h>
#include "vector2.h"


#define TOLERANCE 0.00001f


inline float minf(float f1, float f2) {
	return f1 < f2 ? f1 : f2;
}


inline float maxf(float f1, float f2) {
	return f1 > f2 ? f1 : f2;
}


inline float clampf(float f, float min, float max) {
	return f < min ? min : (f > max ? max : f);
}


inline bool is_zero_approx(float f) {
	return abs(f) < TOLERANCE;
}


inline bool is_equal_approx(float f1, float f2) {
	float x = maxf(f1, f2);
	return abs(f1 - x) < TOLERANCE;
}


#endif
