/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "../vector.hpp"
#include "../matrix.hpp"
#define GAMMA_HAS_TRANSFORM_TRANSLATION

namespace gamma {
namespace transform {

/** A translation transformation. */
template <typename T> struct translation
{
	typedef translation<T> self;
	typedef vector3<T> vector_type;
	typedef matrix4<T> matrix_type;

	vector_type v; // input
	matrix_type m; // output

	translation() {}
	translation(const vector_type& a): v(a) {}

	self& operator+= (const vector_type& a) { v += a; return *this; }
	self& operator-= (const vector_type& a) { v -= a; return *this; }
	self& operator*= (const vector_type& a) { v *= a; return *this; }
	self& operator/= (const vector_type& a) { v /= a; return *this; }
	self& reset() { v = vector_type(); return *this; }

	self operator+ (const vector_type& a) { return self(v + a); }
	self operator- (const vector_type& a) { return self(v - a); }
	self operator* (const vector_type& a) { return self(v * a); }
	self operator/ (const vector_type& a) { return self(v / a); }

	operator matrix_type() const { return m; }

	self& update()
	{
		m = matrix_type(
			1, 0, 0, v.x,
			0, 1, 0, v.y,
			0, 0, 1, v.z,
			0, 0, 0, 1);
		return *this;
	}
};

} // namespace transform
} // namespace gamma