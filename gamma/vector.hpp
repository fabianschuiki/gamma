/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include <stdint.h>
#define GAMMA_HAS_VECTOR

namespace gamma {

// Include the math library into the gamma namespace to avoid name conflicts.
extern "C" {
#include <math.h>
}

/// Two-dimensional vector.
template<typename T> struct vector2
{
	typedef T type;
	typedef vector2<T> self;

	union {
		struct { T x, y; };
		T v[2];
	};
	
	vector2() : x(0), y(0) {}
	explicit vector2(T h) : x(h), y(h) {}
	explicit vector2(T x, T y) : x(x), y(y) {}
	template<typename R> explicit vector2(const vector2<R>& h) : x(h.x), y(h.y) {}

	template<typename R> operator vector2<R>() const { return vector2<R>(*this); }
	T& operator() (int index) { return v[index]; }
	T operator() (int index) const { return v[index]; }
	
	self operator- () const { return self(-x, -y); }
	template<typename R> self& operator= (const vector2<R>& h) { x=h.x; y=h.y; return *this; }
	template<typename R> self& operator= (R h) { x=h; y=h; return *this; }
	
	template<typename R> self mul(const vector2<R>& h) const { return self(x*h.x, y*h.y); }
	template<typename R> self div(const vector2<R>& h) const { return self(x/h.x, y/h.y); }

	template<typename R> self& operator+= (const vector2<R>& h) { x+=h.x; y+=h.y; return *this; }
	template<typename R> self& operator-= (const vector2<R>& h) { x-=h.x; y-=h.y; return *this; }
	template<typename R> self& muleq(const vector2<R>& h) { x*=h.x; y*=h.y; return *this; }
	template<typename R> self& diveq(const vector2<R>& h) { x/=h.x; y/=h.y; return *this; }

	template<typename R> self& operator+= (R h)	{ x+=h; y+=h; return *this; }
	template<typename R> self& operator-= (R h)	{ x-=h; y-=h; return *this; }
	template<typename R> self& operator*= (R h)	{ x*=h; y*=h; return *this; }
	template<typename R> self& operator/= (R h)	{ x/=h; y/=h; return *this; }
	
	T length2() const { return dot(*this); }
	float lengthf() const { return sqrtf(length2()); }
	double length() const { return sqrt(length2()); }

	template<typename R> T dot(const R& h) const { return x*h.x + y*h.y; }
	template<typename R> self ortho() const { return self(y, -x); }
	
	self& normalize() { T l = length(); return *this /= l; }
	self normalized() const { T l = length(); return *this / l; }
};

template<typename T, typename R> vector2<T> operator+ (const vector2<T>& v, const vector2<R>& h) { return vector2<T>(v.x+h.x, v.y+h.y); }
template<typename T, typename R> vector2<T> operator- (const vector2<T>& v, const vector2<R>& h) { return vector2<T>(v.x-h.x, v.y-h.y); }
template<typename T, typename R> T operator* (const vector2<T>& v, const vector2<R>& h) { return v.dot(h); }

template<typename T, typename R> vector2<T> operator+ (R h, const vector2<T>& v) { return vector2<T>(h+v.x, h+v.y); }
template<typename T, typename R> vector2<T> operator- (R h, const vector2<T>& v) { return vector2<T>(h-v.x, h-v.y); }
template<typename T, typename R> vector2<T> operator* (R h, const vector2<T>& v) { return vector2<T>(h*v.x, h*v.y); }
template<typename T, typename R> vector2<T> operator/ (R h, const vector2<T>& v) { return vector2<T>(h/v.x, h/v.y); }

template<typename T, typename R> vector2<T> operator+ (const vector2<T>& v, R h) { return vector2<T>(v.x+h, v.y+h); }
template<typename T, typename R> vector2<T> operator- (const vector2<T>& v, R h) { return vector2<T>(v.x-h, v.y-h); }
template<typename T, typename R> vector2<T> operator* (const vector2<T>& v, R h) { return vector2<T>(v.x*h, v.y*h); }
template<typename T, typename R> vector2<T> operator/ (const vector2<T>& v, R h) { return vector2<T>(v.x/h, v.y/h); }


/// Three-dimensional vector.
template<typename T> struct vector3
{
	typedef T type;
	typedef vector3<T> self;

	union {
		struct { T x, y, z; };
		T v[3];
	};
	
	vector3() : x(0), y(0), z(0) {}
	vector3(T h) : x(h), y(h), z(h) {}
	vector3(T x, T y, T z) : x(x), y(y), z(z) {}
	template<typename R> vector3(const vector3<R>& h) : x(h.x), y(h.y), z(h.z) {}
	template<typename R> vector3(const vector2<R>& h, T z) : x(h.x), y(h.y), z(z) {}
	
	self operator- () const { return self(-x, -y, -z); }
	template<typename R> self& operator= (const vector3<R>& h) { x=h.x; y=h.y; z=h.z; return *this; }
	template<typename R> self& operator= (R h) { x=h; y=h; z=h; return *this; }
	
	template<typename R> self mul(const vector3<R>& h) const { return self(x*h.x, y*h.y, z*h.z); }
	template<typename R> self div(const vector3<R>& h) const { return self(x/h.x, y/h.y, z/h.z); }

	template<typename R> self& operator+= (const vector3<R>& h) { x+=h.x; y+=h.y; z+=h.z; return *this; }
	template<typename R> self& operator-= (const vector3<R>& h) { x-=h.x; y-=h.y; z-=h.z; return *this; }
	template<typename R> self& muleq(const vector3<R>& h) { x*=h.x; y*=h.y; z*=h.z; return *this; }
	template<typename R> self& diveq(const vector3<R>& h) { x/=h.x; y/=h.y; z/=h.z; return *this; }

	template<typename R> self& operator+= (R h)	{ x+=h; y+=h; z+=h; return *this; }
	template<typename R> self& operator-= (R h)	{ x-=h; y-=h; z-=h; return *this; }
	template<typename R> self& operator*= (R h)	{ x*=h; y*=h; z*=h; return *this; }
	template<typename R> self& operator/= (R h)	{ x/=h; y/=h; z/=h; return *this; }
	
	T length2() const { return dot(*this); }
	float lengthf() const { return sqrtf(length2()); }
	double length() const { return sqrt(length2()); }

	template<typename R> T dot(const R& h) const { return x*h.x + y*h.y + z*h.z; }
	template<typename R> self cross(const R& h) const { return self(y*h.z - z*h.y, z*h.x - x*h.z, x*h.y - y*h.x); }
	
	self& normalize() { T l = length(); return *this /= l; }
	self normalized() const { T l = length(); return *this / l; }
};

template<typename T, typename R> vector3<T> operator+ (const vector3<T>& v, const vector3<R>& h) { return vector3<T>(v.x+h.x, v.y+h.y, v.z+h.z); }
template<typename T, typename R> vector3<T> operator- (const vector3<T>& v, const vector3<R>& h) { return vector3<T>(v.x-h.x, v.y-h.y, v.z-h.z); }
template<typename T, typename R> T operator* (const vector3<T>& v, const vector3<R>& h) { return v.dot(h); }

template<typename T, typename R> vector3<T> operator+ (R h, const vector3<T>& v) { return vector3<T>(h+v.x, h+v.y, h+v.z); }
template<typename T, typename R> vector3<T> operator- (R h, const vector3<T>& v) { return vector3<T>(h-v.x, h-v.y, h-v.z); }
template<typename T, typename R> vector3<T> operator* (R h, const vector3<T>& v) { return vector3<T>(h*v.x, h*v.y, h*v.z); }
template<typename T, typename R> vector3<T> operator/ (R h, const vector3<T>& v) { return vector3<T>(h/v.x, h/v.y, h/v.z); }

template<typename T, typename R> vector3<T> operator+ (const vector3<T>& v, R h) { return vector3<T>(v.x+h, v.y+h, v.z+h); }
template<typename T, typename R> vector3<T> operator- (const vector3<T>& v, R h) { return vector3<T>(v.x-h, v.y-h, v.z-h); }
template<typename T, typename R> vector3<T> operator* (const vector3<T>& v, R h) { return vector3<T>(v.x*h, v.y*h, v.z*h); }
template<typename T, typename R> vector3<T> operator/ (const vector3<T>& v, R h) { return vector3<T>(v.x/h, v.y/h, v.z/h); }


/// Four-dimensional vector.
template<typename T> struct vector4
{
	typedef T type;
	typedef vector4<T> self;

	union {
		struct { T x, y, z, w; };
		T v[4];
	};
	
	vector4() : x(0), y(0), z(0), w(0) {}
	vector4(T h) : x(h), y(h), z(h), w(h) {}
	vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	template<typename R> vector4(const vector4<R>& h) : x(h.x), y(h.y), z(h.z), w(h.w) {}
	template<typename R> vector4(const vector3<R>& h, T w) : x(h.x), y(h.y), z(h.z), w(w) {}
	template<typename R> vector4(const vector2<R>& h, T z, T w) : x(h.x), y(h.y), z(z), w(w) {}
	
	self operator- () const { return self(-x, -y, -z, -w); }
	template<typename R> self& operator= (const vector4<R>& h) { x=h.x; y=h.y; z=h.z; w=h.w; return *this; }
	template<typename R> self& operator= (R h) { x=h; y=h; z=h; w=h; return *this; }
	
	template<typename R> self mul(const vector4<R>& h) const { return self(x*h.x, y*h.y, z*h.z, w*h.w); }
	template<typename R> self div(const vector4<R>& h) const { return self(x/h.x, y/h.y, z/h.z, w/h.w); }

	template<typename R> self& operator+= (const vector4<R>& h) { x+=h.x; y+=h.y; z+=h.z; w+=h.w; return *this; }
	template<typename R> self& operator-= (const vector4<R>& h) { x-=h.x; y-=h.y; z-=h.z; w-=h.w; return *this; }
	template<typename R> self& muleq(const vector4<R>& h) { x*=h.x; y*=h.y; z*=h.z; w*=h.w; return *this; }
	template<typename R> self& diveq(const vector4<R>& h) { x/=h.x; y/=h.y; z/=h.z; w/=h.w; return *this; }

	template<typename R> self& operator+= (R h)	{ x+=h; y+=h; z+=h; w+=h; return *this; }
	template<typename R> self& operator-= (R h)	{ x-=h; y-=h; z-=h; w-=h; return *this; }
	template<typename R> self& operator*= (R h)	{ x*=h; y*=h; z*=h; w*=h; return *this; }
	template<typename R> self& operator/= (R h)	{ x/=h; y/=h; z/=h; w/=h; return *this; }
	
	T length2() const { return dot(*this); }
	float lengthf() const { return sqrtf(length2()); }
	double length() const { return sqrt(length2()); }

	template<typename R> T dot(const R& h) const { return x*h.x + y*h.y + z*h.z + w*h.w; }
	
	self& normalize() { T l = length(); return *this /= l; }
	self normalized() const { T l = length(); return *this / l; }
};

template<typename T, typename R> vector4<T> operator+ (const vector4<T>& v, const vector4<R>& h) { return vector4<T>(v.x+h.x, v.y+h.y, v.z+h.z, v.w+h.w); }
template<typename T, typename R> vector4<T> operator- (const vector4<T>& v, const vector4<R>& h) { return vector4<T>(v.x-h.x, v.y-h.y, v.z-h.z, v.w-h.w); }
template<typename T, typename R> T operator* (const vector4<T>& v, const vector4<R>& h) { return v.dot(h); }

template<typename T, typename R> vector4<T> operator+ (R h, const vector4<T>& v) { return vector4<T>(h+v.x, h+v.y, h+v.z, h+v.w); }
template<typename T, typename R> vector4<T> operator- (R h, const vector4<T>& v) { return vector4<T>(h-v.x, h-v.y, h-v.z, h-v.w); }
template<typename T, typename R> vector4<T> operator* (R h, const vector4<T>& v) { return vector4<T>(h*v.x, h*v.y, h*v.z, h*v.w); }
template<typename T, typename R> vector4<T> operator/ (R h, const vector4<T>& v) { return vector4<T>(h/v.x, h/v.y, h/v.z, h/v.w); }

template<typename T, typename R> vector4<T> operator+ (const vector4<T>& v, R h) { return vector4<T>(v.x+h, v.y+h, v.z+h, v.w+h); }
template<typename T, typename R> vector4<T> operator- (const vector4<T>& v, R h) { return vector4<T>(v.x-h, v.y-h, v.z-h, v.w-h); }
template<typename T, typename R> vector4<T> operator* (const vector4<T>& v, R h) { return vector4<T>(v.x*h, v.y*h, v.z*h, v.w*h); }
template<typename T, typename R> vector4<T> operator/ (const vector4<T>& v, R h) { return vector4<T>(v.x/h, v.y/h, v.z/h, v.w/h); }


namespace convenience {
	typedef vector2<uint8_t> vector2b;
	typedef vector3<uint8_t> vector3b;
	typedef vector4<uint8_t> vector4b;

	typedef vector2<int> vector2i;
	typedef vector3<int> vector3i;
	typedef vector4<int> vector4i;

	typedef vector2<float> vector2f;
	typedef vector3<float> vector3f;
	typedef vector4<float> vector4f;

	typedef vector2<double> vector2d;
	typedef vector3<double> vector3d;
	typedef vector4<double> vector4d;
}
} // namespace gamma