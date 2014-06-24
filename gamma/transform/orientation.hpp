/* Copyright (c) 2013-2014 Fabian Schuiki */
#pragma once
#include "gamma/vector.hpp"
#include "gamma/matrix.hpp"
#define GAMMA_HAS_TRANSFORM_ORIENTATE

namespace gma {
namespace transform {

/// A rotation transformation that constructs a new subspace given two vectors.
/// The target vector becomes the new Z component, and the X and Y are
/// constructed as a right-hand-system based on the cross products between
/// target and up. This transformation performs the rotation component of the
/// gluLookAt function.
template <typename T> struct orientation
{
	typedef orientation<T> self;
	typedef T scalar_type;
	typedef vector3<T> vector_type;
	typedef matrix4<T> matrix_type;

	const vector_type target;
	const vector_type up;

	orientation(): m(1) {}
	orientation(const vector_type& target, const vector_type& up):
		target(target),
		up(up) {

		// construct the base vectors for the transformation
		vector_type N = target.normalized();      // Z component of the new space
		vector_type U = N.cross(up).normalized(); // X component of the new space
		vector_type V = U.cross(N);               // Y component of the new space

		m = matrix_type(
			 U.x,   U.y,   U.z,  0,
			 V.x,   V.y,   V.z,  0,
			-N.x,  -N.y,  -N.z,  0,
			   0,     0,     0,  1
		);
	}

	operator matrix_type() const { return m; }

private:
	matrix_type m;
};

typedef orientation<float>  orientationf;
typedef orientation<double> orientationd;

} // namespace transform
} // namespace gma
