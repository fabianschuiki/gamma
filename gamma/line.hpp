/* Copyright (c) 2013-2014 Fabian Schuiki */
#pragma once
#include "gamma/vector.hpp"
#define GAMMA_HAS_LINE

namespace gma {

/// A line in arbitrary dimensions, as defined by a point and a direection.
template <typename T> struct line
{
	typedef typename T::Type scalar_type;
	typedef T vector_type;
	typedef line<T> self;

	T p, d;

	line() {}
	line(const vector_type &p, const vector_type &d) : p(p), d(d) {}
};

namespace convenience {
	typedef line<vector2b> line2b;
	typedef line<vector3b> line3b;
	typedef line<vector4b> line4b;

	typedef line<vector2i> line2i;
	typedef line<vector3i> line3i;
	typedef line<vector4i> line4i;

	typedef line<vector2f> line2f;
	typedef line<vector3f> line3f;
	typedef line<vector4f> line4f;

	typedef line<vector2d> line2d;
	typedef line<vector3d> line3d;
	typedef line<vector4d> line4d;
}
} // namespace gma
