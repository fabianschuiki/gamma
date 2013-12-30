/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "../math.hpp"
#include "../vector.hpp"
#include "../matrix.hpp"
#define GAMMA_HAS_TRANSFORM_Y_ROTATION

namespace gamma {
namespace transform {

/** A rotation about the y axis. */
template <typename T> struct y_rotation
{
	typedef y_rotation<T> self;
	typedef T scalar_type;
	typedef matrix4<T> matrix_type;

	scalar_type y; // input
	matrix_type m; // output

	y_rotation() {}
	y_rotation(const scalar_type& a): y(a) {}

	self& operator+= (const scalar_type& a) { y += a; return *this; }
	self& operator-= (const scalar_type& a) { y -= a; return *this; }
	self& operator*= (const scalar_type& a) { y *= a; return *this; }
	self& operator/= (const scalar_type& a) { y /= a; return *this; }
	self& reset() { y = 0; return *this; }

	self operator+ (const scalar_type& a) { return self(y + a); }
	self operator- (const scalar_type& a) { return self(y - a); }
	self operator* (const scalar_type& a) { return self(y * a); }
	self operator/ (const scalar_type& a) { return self(y / a); }

	operator matrix_type() const { return m; }

	self& update()
	{
		m = matrix_type(
			cos(y), 0, -sin(y), 0,
			     0, 1,       0, 0,
			sin(y), 0,  cos(y), 0,
			     0, 0,       0, 1);
		return *this;
	}
};

} // namespace transform
} // namespace gamma