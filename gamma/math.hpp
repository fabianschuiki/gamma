/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#define GAMMA_HAS_MATH

// Use a define to resolve a name conflict in cmath.
#if defined(_MATH_H) || defined(_MATH_H_)
#error "You have included math.h or cmath before gamma/math.hpp. This causes a name collision. Please put #include <gamma/math.hpp> before any other includes."
#endif

#define gamma cmath_gamma
#include <cmath>
extern "C" {
	#include <stdint.h>
}
#undef gamma