/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "matrix.hpp"

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
	template <typename R> translation(const R& a): v(a) {}

	template <typename R> self& operator+= (const translation<R>& a) { v += a.v; return *this; }
	template <typename R> self& operator-= (const translation<R>& a) { v -= a.v; return *this; }
	template <typename R> self& operator+= (const vector3<R>& a) { v += a; return *this; }
	template <typename R> self& operator-= (const vector3<R>& a) { v -= a; return *this; }
	self& reset() { v = vector_type(); return *this; }

	template <typename R> self operator+ (const translation<R>& a) { return self(v + a.v); }
	template <typename R> self operator- (const translation<R>& a) { return self(v - a.v); }
	template <typename R> self operator+ (const vector3<R>& a) { return self(v + a); }
	template <typename R> self operator- (const vector3<R>& a) { return self(v - a); }

	operator vector_type() const { return v; }
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