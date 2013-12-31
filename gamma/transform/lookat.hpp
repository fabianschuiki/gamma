/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "translation.hpp"
#include "orientation.hpp"
#define GAMMA_HAS_TRANSFORM_LOOKAT

namespace gamma {
namespace transform {

/** A compound transformation that moves the space origin to the given position
 * and orientations the whole space such that its Z axis points along %target.
 * See the orientation transform for details. */
template <typename T> struct lookat
{
	typedef lookat<T> self;
	typedef T scalar_type;
	typedef vector3<T> vector_type;
	typedef matrix4<T> matrix_type;

	const translation<T> translate;
	const orientation<T> orientate;

	lookat() {}
	lookat(const translation<T>& translate, const orientation<T>& orientate): translate(translate), orientate(orientate) { init(); }
	lookat(const vector_type& position, const vector_type& target, const vector_type& up): translate(-position), orientate(target, up) { init(); }

	operator matrix_type() const { return m; }

private:
	matrix_type m;
	void init() { m = (matrix_type)orientate * (matrix_type)translate; }
};

typedef lookat<float>  lookatf;
typedef lookat<double> lookatd;

} // namespace transform
} // namespace gamma