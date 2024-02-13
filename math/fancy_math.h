#ifndef FANCY_MATH_H
#define FANCY_MATH_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <QtGlobal>
#include "vector2.h"


#define TOLERANCE 0.00001f


inline qreal minf(qreal f1, qreal f2) {
	return f1 < f2 ? f1 : f2;
}


inline qreal maxf(qreal f1, qreal f2) {
	return f1 > f2 ? f1 : f2;
}


inline qreal clampf(qreal f, qreal min, qreal max) {
	return f < min ? min : (f > max ? max : f);
}


inline bool is_zero_approx(qreal f) {
	return abs(f) < TOLERANCE;
}


inline bool is_equal_approx(qreal f1, qreal f2) {
	qreal x = maxf(f1, f2);
	return abs(f1 - x) < TOLERANCE;
}


#endif
