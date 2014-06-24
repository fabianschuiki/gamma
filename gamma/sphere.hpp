/* Copyright (c) 2013-2014 Fabian Schuiki */
#pragma once
#include "gamma/vector.hpp"
#define GAMMA_HAS_SPHERE

namespace gma {

/// A sphere in arbitrary dimensions, as defined by its center and radius.
template <typename T> struct sphere
{
	typedef typename T::type scalar_type;
	typedef T vector_type;
	typedef sphere<T> self;

	vector_type c; // center
	scalar_type r; // radius

	sphere(): c(), r(0) {}
	sphere(const vector_type &c): c(c), r(1) {}
	sphere(const vector_type &c, const scalar_type &r): c(c), r(r) {}
};

namespace convenience {
	typedef sphere<vector2b> sphere2b;
	typedef sphere<vector3b> sphere3b;
	typedef sphere<vector4b> sphere4b;

	typedef sphere<vector2i> sphere2i;
	typedef sphere<vector3i> sphere3i;
	typedef sphere<vector4i> sphere4i;

	typedef sphere<vector2f> sphere2f;
	typedef sphere<vector3f> sphere3f;
	typedef sphere<vector4f> sphere4f;

	typedef sphere<vector2d> sphere2d;
	typedef sphere<vector3d> sphere3d;
	typedef sphere<vector4d> sphere4d;
}
} // namespace gma
