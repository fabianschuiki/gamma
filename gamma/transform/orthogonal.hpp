/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "../math.hpp"
#include "../matrix.hpp"
#define GAMMA_HAS_TRANSFORM_ORTHOGONAL

namespace gamma {
namespace transform {

/** A parallel projection, as it would be generated by the glOrtho OpenGL call. */
template <typename T> struct orthogonal
{
	typedef orthogonal<T> self;
	typedef T scalar_type;
	typedef matrix4<T> matrix_type;

	const T left, right;
	const T bottom, top;
	const T near, far;

	orthogonal(): m(1) {}
	orthogonal(T left, T right, T bottom, T top, T near, T far): left(left), right(right), bottom(bottom), top(top), near(near), far(far)
	{
		T fx = 2 / (right-left);
		T fy = 2 / (top-bottom);
		T fz = 2 / (far-near);
		T tx = -(right+left)/(right-left);
		T ty = -(top+bottom)/(top-bottom);
		T tz = -(far+near)/(far-near);
		m = matrix_type(
			fx,   0,    0,  tx,
			 0,  fy,    0,  ty,
			 0,   0,  -fz,  tz,
			 0,   0,    0,   1
		);
	}

	operator matrix_type() const { return m; }

protected:
	matrix_type m;
};

typedef orthogonal<float>  orthogonalf;
typedef orthogonal<double> orthogonald;

} // namespace transform
} // namespace gamma