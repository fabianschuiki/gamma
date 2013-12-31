/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "../math.hpp"
#include "../matrix.hpp"
#define GAMMA_HAS_TRANSFORM_PERSPECTIVE

namespace gamma {
namespace transform {

/** A perspective projection, as it would be generated by the gluPerspective
 * OpenGL call. Note that the field-of-view is vertical, aspect is the ratio
 * between the horizontal and vertical field-of-view, and near and far refer to
 * the near and far clipping planes. */
template <typename T> struct perspective
{
	typedef perspective<T> self;
	typedef T scalar_type;
	typedef matrix4<T> matrix_type;

	const T fov; // vertical field of view [radians]
	const T aspect;
	const T near, far; // clipping planes

	perspective(): m(1) {}
	perspective(T fov, T aspect, T near, T far): fov(fov), aspect(aspect), near(near), far(far)
	{
		T f = tan(M_PI_2 - fov/2); // cot(x) = tan(pi/2 - x)
		T g = f/aspect;
		T a = near+far;
		T b = near-far;
		T c = 2*near*far;
		m = matrix_type(
			g,  0,    0,    0,
			0,  f,    0,    0,
			0,  0,  a/b,  c/b,
			0,  0,   -1,    0
		);
	}

	operator matrix_type() const { return m; }

protected:
	matrix_type m;
};

typedef perspective<float>  perspectivef;
typedef perspective<double> perspectived;

} // namespace transform
} // namespace gamma