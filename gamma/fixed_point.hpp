/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "math.hpp"
#define GAMMA_HAS_FIXED_POINT

namespace gamma {

/** @brief Class for fixed-point arithmetics.
 *
 * The template parameter T configures the storage type for the fixed-point
 * number. Usually one of the integer types char, short, int, long, long long.
 * Parameter P configures the precision, i.e. how many decimal bits the number
 * has. */
template<typename T, int P> struct fixed_point
{
	typedef fixed_point<T,P> self;
	typedef T value_type;

	const static int precision = P;
	const static T factor = ((T)1) << P;
	const static T decimal_mask = factor - 1;

	T v;

	fixed_point() {}
	template<typename R> fixed_point(R r, int f = 1) : v(r * factor / f) {}
	fixed_point(const self& f) : v(f.v) {}
	template<typename R, int S> fixed_point(const fixed_point<R,S>& f) : v(f.v * factor / f.factor) {}

	self operator- () const { return self(-v, factor); }
	template<typename R> self& operator= (R r) { v = r * factor; return *this; }
	self& operator= (const self& f) { v = f.v; return *this; }
	template<typename R, int S> self& operator= (const fixed_point<R,S>& f) { v = f.v * factor / f.factor; return *this; }

	self operator+ (const self& r) const { return self(v + r.v, factor); }
	self operator- (const self& r) const { return self(v - r.v, factor); }
	self operator* (const self& r) const { return self(v * r.v / factor, factor); }
	self operator/ (const self& r) const { return self(v * factor / r.v, factor); }

	template<typename R> self& operator+= (R r) { v += r*factor; return *this; }
	template<typename R> self& operator-= (R r) { v -= r*factor; return *this; }
	template<typename R> self& operator*= (R r) { v *= r; return *this; }
	template<typename R> self& operator/= (R r) { v /= r; return *this; }

	template<typename R, int S> self& operator+= (const fixed_point<R,S>& f) { v += (f.v * factor / f.factor); return *this; }
	template<typename R, int S> self& operator-= (const fixed_point<R,S>& f) { v -= (f.v * factor / f.factor); return *this; }
	template<typename R, int S> self& operator*= (const fixed_point<R,S>& f) { v = (v * f.v / f.factor); return *this; }
	template<typename R, int S> self& operator/= (const fixed_point<R,S>& f) { v = (v * f.factor / f.v); return *this; }

	self& operator+= (const self& r) { v += r.v; return *this; }
	self& operator-= (const self& r) { v -= r.v; return *this; }
	self& operator*= (const self& r) { v = v * r.v / factor; return *this; }
	self& operator/= (const self& r) { v = v * factor / r.v; return *this; }

	template<typename R> operator R() const { return (R)v / factor; }
	template<typename R, int S> operator fixed_point<R,S>() const { return fixed_point<R,S>(v * fixed_point<R,S>::factor / factor); }

	self round() const { return self((v & ~decimal_mask) + ((v & decimal_mask) >= factor/2 ? factor : 0) & ~decimal_mask, factor); }
	self floor() const { return self((v & ~decimal_mask), factor); }
	self ceil() const { return self((v & ~decimal_mask) + ((v & decimal_mask) > 0 ? factor : 0) & ~decimal_mask, factor); }
};

template<typename R, typename S, int T> fixed_point<S,T> operator+ (R r, const fixed_point<S,T>& f) { return fixed_point<S,T>((S)(r*f.factor + f.v), f.factor); }
template<typename R, typename S, int T> fixed_point<S,T> operator- (R r, const fixed_point<S,T>& f) { return fixed_point<S,T>((S)(r*f.factor - f.v), f.factor); }
template<typename R, typename S, int T> fixed_point<S,T> operator* (R r, const fixed_point<S,T>& f) { return fixed_point<S,T>((S)(r * f.v), f.factor); }
template<typename R, typename S, int T> fixed_point<S,T> operator/ (R r, const fixed_point<S,T>& f) { return fixed_point<S,T>((S)(r * f.factor * f.factor / f.v), f.factor); }

template<typename R, typename S, int T> fixed_point<S,T> operator+ (const fixed_point<S,T>& f, R r) { return fixed_point<S,T>((S)(f.v + r*f.factor), f.factor); }
template<typename R, typename S, int T> fixed_point<S,T> operator- (const fixed_point<S,T>& f, R r) { return fixed_point<S,T>((S)(f.v - r*f.factor), f.factor); }
template<typename R, typename S, int T> fixed_point<S,T> operator* (const fixed_point<S,T>& f, R r) { return fixed_point<S,T>((S)(f.v * r), f.factor); }
template<typename R, typename S, int T> fixed_point<S,T> operator/ (const fixed_point<S,T>& f, R r) { return fixed_point<S,T>((S)(f.v / r), f.factor); }

template<typename R, int S, typename T, int U> fixed_point<T,U> operator+ (const fixed_point<R,S>& a, const fixed_point<T,U>& b) { return fixed_point<T,U>(a.v + (b.v * a.factor / b.factor), a.factor); }
template<typename R, int S, typename T, int U> fixed_point<T,U> operator- (const fixed_point<R,S>& a, const fixed_point<T,U>& b) { return fixed_point<T,U>(a.v - (b.v * a.factor / b.factor), a.factor); }
template<typename R, int S, typename T, int U> fixed_point<T,U> operator* (const fixed_point<R,S>& a, const fixed_point<T,U>& b) { return fixed_point<T,U>((T)(a.v * b.v / b.factor), a.factor); }
template<typename R, int S, typename T, int U> fixed_point<T,U> operator/ (const fixed_point<R,S>& a, const fixed_point<T,U>& b) { return fixed_point<T,U>((T)(a.v * b.factor / b.v), a.factor); }

template<typename R, int S, typename T, int U> bool operator> (const fixed_point<R,S>& a, const fixed_point<T,U>& b) { return a.v*b.factor > b.v*a.factor; }
template<typename R, int S, typename T, int U> bool operator< (const fixed_point<R,S>& a, const fixed_point<T,U>& b) { return a.v*b.factor < b.v*a.factor; }
template<typename R, int S, typename T, int U> bool operator>= (const fixed_point<R,S>& a, const fixed_point<T,U>& b) { return a.v*b.factor >= b.v*a.factor; }
template<typename R, int S, typename T, int U> bool operator<= (const fixed_point<R,S>& a, const fixed_point<T,U>& b) { return a.v*b.factor <= b.v*a.factor; }
template<typename R, int S, typename T, int U> bool operator== (const fixed_point<R,S>& a, const fixed_point<T,U>& b) { return a.v*b.factor == b.v*a.factor; }
template<typename R, int S, typename T, int U> bool operator!= (const fixed_point<R,S>& a, const fixed_point<T,U>& b) { return a.v*b.factor != b.v*a.factor; }

template<typename R, typename S, int T> bool operator> (R r, const fixed_point<S,T>& f) { return r*f.factor > f.v; }
template<typename R, typename S, int T> bool operator< (R r, const fixed_point<S,T>& f) { return r*f.factor < f.v; }
template<typename R, typename S, int T> bool operator>= (R r, const fixed_point<S,T>& f) { return r*f.factor >= f.v; }
template<typename R, typename S, int T> bool operator<= (R r, const fixed_point<S,T>& f) { return r*f.factor <= f.v; }
template<typename R, typename S, int T> bool operator== (R r, const fixed_point<S,T>& f) { return r*f.factor == f.v; }
template<typename R, typename S, int T> bool operator!= (R r, const fixed_point<S,T>& f) { return r*f.factor != f.v; }

template<typename R, typename S, int T> bool operator> (const fixed_point<S,T>& f, R r) { return r < f; }
template<typename R, typename S, int T> bool operator< (const fixed_point<S,T>& f, R r) { return r > f; }
template<typename R, typename S, int T> bool operator>= (const fixed_point<S,T>& f, R r) { return r <= f; }
template<typename R, typename S, int T> bool operator<= (const fixed_point<S,T>& f, R r) { return r >= f; }
template<typename R, typename S, int T> bool operator== (const fixed_point<S,T>& f, R r) { return r == f; }
template<typename R, typename S, int T> bool operator!= (const fixed_point<S,T>& f, R r) { return r != f; }

} // namespace gamma