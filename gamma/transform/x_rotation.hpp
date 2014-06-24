/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "gamma/math.hpp"
#include "gamma/vector.hpp"
#include "gamma/matrix.hpp"
#define GAMMA_HAS_TRANSFORM_X_ROTATION

namespace gma {
namespace transform {

/// A rotation about the x axis.
template <typename T> struct x_rotation
{
	typedef x_rotation<T> self;
	typedef T scalar_type;
	typedef matrix4<T> matrix_type;

	scalar_type x; // input
	matrix_type m; // output

	x_rotation() {}
	x_rotation(const scalar_type& a): x(a) {}

	self& operator+= (const scalar_type& a) { x += a; return *this; }
	self& operator-= (const scalar_type& a) { x -= a; return *this; }
	self& operator*= (const scalar_type& a) { x *= a; return *this; }
	self& operator/= (const scalar_type& a) { x /= a; return *this; }
	self& reset() { x = 0; return *this; }

	self operator+ (const scalar_type& a) { return self(x + a); }
	self operator- (const scalar_type& a) { return self(x - a); }
	self operator* (const scalar_type& a) { return self(x * a); }
	self operator/ (const scalar_type& a) { return self(x / a); }

	operator matrix_type() const { return m; }

	self& update()
	{
		m = matrix_type(
			1,      0,       0, 0,
			0, cos(x), -sin(x), 0,
			0, sin(x),  cos(x), 0,
			0,      0,       0, 1);
		return *this;
	}
};

} // namespace transform
} // namespace gma
