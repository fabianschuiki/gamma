/* Copyright (c) 2013-2014 Fabian Schuiki */
#pragma once
#include "gamma/transform/x_rotation.hpp"
#include "gamma/transform/y_rotation.hpp"
#include "gamma/transform/z_rotation.hpp"

namespace gma {
namespace transform {

/// A rotation transformation about the x, y and z axis. This is a composite
/// transformation using three separate transforms for x, y and z underneath.
/// The individual rotation axis are accessible as mx, my and mz.
template <typename T> struct axial_rotation
{
	typedef axial_rotation<T> self;
	typedef vector3<T> vector_type;
	typedef matrix4<T> matrix_type;

	vector_type v; // input
	x_rotation<T> mx; // intermediate x rotation
	y_rotation<T> my; // intermediate y rotation
	z_rotation<T> mz; // intermediate z rotation
	matrix_type m; // output

	axial_rotation() {}
	axial_rotation(const vector_type& a): v(a) {}

	self& operator+= (const vector_type& a) { v += a; return *this; }
	self& operator-= (const vector_type& a) { v -= a; return *this; }
	self& operator*= (const vector_type& a) { v.muleq(a); return *this; }
	self& operator/= (const vector_type& a) { v.diveq(a); return *this; }
	self& reset() { v = vector_type(); return *this; }

	self operator+ (const vector_type& a) { return self(v + a); }
	self operator- (const vector_type& a) { return self(v - a); }
	self operator* (const vector_type& a) { return self(v.mul(a)); }
	self operator/ (const vector_type& a) { return self(v.div(a)); }

	operator matrix_type() const { return m; }

	self& update()
	{
		mx.x = v.x; mx.update();
		my.y = v.y; my.update();
		mz.z = v.z; mz.update();
		m = (mz*my)*mx;
		return *this;
	}
};

} // namespace transform
} // namespace gma
