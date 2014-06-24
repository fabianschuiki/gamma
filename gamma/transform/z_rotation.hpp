/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "gamma/math.hpp"
#include "gamma/vector.hpp"
#include "gamma/matrix.hpp"
#define GAMMA_HAS_TRANSFORM_Z_ROTATION

namespace gma {
namespace transform {

/// A rotation about the z axis.
template <typename T> struct z_rotation
{
	typedef z_rotation<T> self;
	typedef T scalar_type;
	typedef matrix4<T> matrix_type;

	/// Input angle.
	scalar_type z;
	/// Output rotation matrix.
	matrix_type m; // output

	z_rotation() {}
	z_rotation(const scalar_type& a): z(a) {}

	self& operator+= (const scalar_type& a) { z += a; return *this; }
	self& operator-= (const scalar_type& a) { z -= a; return *this; }
	self& operator*= (const scalar_type& a) { z *= a; return *this; }
	self& operator/= (const scalar_type& a) { z /= a; return *this; }
	self& reset() { z = 0; return *this; }

	self operator+ (const scalar_type& a) { return self(z + a); }
	self operator- (const scalar_type& a) { return self(z - a); }
	self operator* (const scalar_type& a) { return self(z * a); }
	self operator/ (const scalar_type& a) { return self(z / a); }

	operator matrix_type() const { return m; }

	self& update()
	{
		m = matrix_type(
			cos(z), -sin(z), 0, 0,
			sin(z),  cos(z), 0, 0,
			     0,       0, 1, 0,
			     0,       0, 0, 1);
		return *this;
	}
};

} // namespace transform
} // namespace gma
