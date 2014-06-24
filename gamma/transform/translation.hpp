/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "gamma/vector.hpp"
#include "gamma/matrix.hpp"
#define GAMMA_HAS_TRANSFORM_TRANSLATION

namespace gma {
namespace transform {

/// A translation transformation.
template <typename T> struct translation
{
	typedef translation<T> self;
	typedef T scalar_type;
	typedef vector3<T> vector_type;
	typedef matrix4<T> matrix_type;

	const vector_type v;

	translation(): m(1) {}
	translation(const vector_type& v): v(v)
	{
		m = matrix_type(
			1,  0,  0,  v.x,
			0,  1,  0,  v.y,
			0,  0,  1,  v.z,
			0,  0,  0,    1
		);
	}

	operator matrix_type() const { return m; }

private:
	matrix_type m;
};

typedef translation<float>  translationf;
typedef translation<double> translationd;

} // namespace transform
} // namespace gma
