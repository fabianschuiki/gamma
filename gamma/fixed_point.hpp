/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "math.hpp"
#include "integer.hpp"
#define GAMMA_HAS_FIXED_POINT

namespace gamma {

#define recast(bits,thing) ((typename integer::signed_integer<bits>::type)(thing))

/** Class for signed fixed-point arithmetics. */
template<int Ia, int Da> struct fixed_point
{
	typedef fixed_point<Ia,Da> self;

	const static int integral_bits = Ia;
	const static int decimal_bits = Da;
	const static int bits = integral_bits + decimal_bits;

	typedef typename integer::signed_integer<bits>::type value_type;
	#define expand_bits(b, thing) ((si(bits + b))(thing))
	#define expand_bytes(b, thing) expand_bits(b*8, thing)

	const static value_type factor = 1 << (value_type)decimal_bits;
	const static value_type decimal_mask = factor - 1;

	value_type v;

	fixed_point() {}
	fixed_point(const self& f) : v(f.v) {}
	template<typename R> explicit fixed_point(R r, int db = 0) : v(recast(sizeof(r)*8+Da, r) * factor / (1 << (int64_t)db)) {}
	template<int Ib, int Db> explicit fixed_point(const fixed_point<Ia,Da>& f) : v(recast(Ib+Db+Da, f.v) * factor / f.factor) {}

	self operator- () const { return (self){-v}; }
	template<typename R> self& operator= (R r) { v = recast(sizeof(r)*8+Da, r) * factor; return *this; }
	self& operator= (const self& f) { v = f.v; return *this; }
	template<int Ib, int Db> self& operator= (const fixed_point<Ia,Da>& f) { v = recast(Ib+Db+Da, f.v) * factor / f.factor; return *this; }

	template<typename R> self& operator+= (R r) { v += r * (value_type)factor; return *this; }
	template<typename R> self& operator-= (R r) { v -= r * (value_type)factor; return *this; }
	template<typename R> self& operator*= (R r) { v *= r; return *this; }
	template<typename R> self& operator/= (R r) { v /= r; return *this; }

	template<int Ib, int Db> self& operator+= (fixed_point<Ib,Db> f) { v += recast(Ib+Db+Da, f.v) * factor / f.factor; return *this; }
	template<int Ib, int Db> self& operator-= (fixed_point<Ib,Db> f) { v -= recast(Ib+Db+Da, f.v) * factor / f.factor; return *this; }
	template<int Ib, int Db> self& operator*= (fixed_point<Ib,Db> f) { v = recast(Ia+Da+Ib+Db, v) * f.v / f.factor; return *this; }
	template<int Ib, int Db> self& operator/= (fixed_point<Ib,Db> f) { v = recast(Ia+Da+Db, v) * f.factor / f.v; return *this; }

	template<typename R> operator R() const { return (R)v / factor; }
	template<int Ib, int Db> operator fixed_point<Ib,Db>() const { fixed_point<Ib,Db> r; r.v = recast(Ia+Da+Db, v) * r.factor / factor; return r; }

	self round() const { self r; r.v = (v & ~decimal_mask); if ((v & decimal_mask) >= factor/2) r.v += factor; return r; }
	self floor() const { self r; r.v = (v & ~decimal_mask); return r; }
	self ceil()  const { self r; r.v = (v & ~decimal_mask); if ((v & decimal_mask) > 0) r.v += factor; return r; }
};

#define return_wrapped(value) fixed_point<Ia,Da> _r; _r.v = (value); return _r;

template<typename R, int Ia, int Da> fixed_point<Ia,Da> operator+ (R r, fixed_point<Ia,Da> f) { return_wrapped(r * recast(Ia+Da+Da, f.factor) + f.v); }
template<typename R, int Ia, int Da> fixed_point<Ia,Da> operator- (R r, fixed_point<Ia,Da> f) { return_wrapped(r * recast(Ia+Da+Da, f.factor) - f.v); }
template<typename R, int Ia, int Da> fixed_point<Ia,Da> operator* (R r, fixed_point<Ia,Da> f) { return_wrapped(r * f.v); }
template<typename R, int Ia, int Da> fixed_point<Ia,Da> operator/ (R r, fixed_point<Ia,Da> f) { return_wrapped(r * recast(Ia+Da+Da+Da, f.factor) * f.factor / f.v); }

template<typename R, int Ia, int Da> fixed_point<Ia,Da> operator+ (fixed_point<Ia,Da> f, R r) { return_wrapped(f.v + r * recast(Ia+Da+Da, f.factor)); }
template<typename R, int Ia, int Da> fixed_point<Ia,Da> operator- (fixed_point<Ia,Da> f, R r) { return_wrapped(f.v - r * recast(Ia+Da+Da, f.factor)); }
template<typename R, int Ia, int Da> fixed_point<Ia,Da> operator* (fixed_point<Ia,Da> f, R r) { return_wrapped(f.v * r); }
template<typename R, int Ia, int Da> fixed_point<Ia,Da> operator/ (fixed_point<Ia,Da> f, R r) { return_wrapped(f.v / r); }

template<int Ia, int Da, int Ib, int Db> fixed_point<Ia,Da> operator+ (fixed_point<Ia,Da> a, fixed_point<Ib,Db> b) { return_wrapped(a.v + (recast(Ib+Db+Da, b.v) * a.factor / b.factor)); }
template<int Ia, int Da, int Ib, int Db> fixed_point<Ia,Da> operator- (fixed_point<Ia,Da> a, fixed_point<Ib,Db> b) { return_wrapped(a.v - (recast(Ib+Db+Da, b.v) * a.factor / b.factor)); }
template<int Ia, int Da, int Ib, int Db> fixed_point<Ia,Da> operator* (fixed_point<Ia,Da> a, fixed_point<Ib,Db> b) { return_wrapped(recast(Ia+Da+Ib+Db, a.v) * b.v / b.factor); }
template<int Ia, int Da, int Ib, int Db> fixed_point<Ia,Da> operator/ (fixed_point<Ia,Da> a, fixed_point<Ib,Db> b) { return_wrapped(recast(Ia+Da+Db, a.v) * b.factor / b.v); }

template<int Ia, int Da, int Ib, int Db> bool operator>  (fixed_point<Ia,Da> a, fixed_point<Ib,Db> b) { return recast(Ia+Da+Db, a.v) * b.factor >  recast(Ib+Db+Da, b.v) * a.factor; }
template<int Ia, int Da, int Ib, int Db> bool operator<  (fixed_point<Ia,Da> a, fixed_point<Ib,Db> b) { return recast(Ia+Da+Db, a.v) * b.factor <  recast(Ib+Db+Da, b.v) * a.factor; }
template<int Ia, int Da, int Ib, int Db> bool operator>= (fixed_point<Ia,Da> a, fixed_point<Ib,Db> b) { return recast(Ia+Da+Db, a.v) * b.factor >= recast(Ib+Db+Da, b.v) * a.factor; }
template<int Ia, int Da, int Ib, int Db> bool operator<= (fixed_point<Ia,Da> a, fixed_point<Ib,Db> b) { return recast(Ia+Da+Db, a.v) * b.factor <= recast(Ib+Db+Da, b.v) * a.factor; }
template<int Ia, int Da, int Ib, int Db> bool operator== (fixed_point<Ia,Da> a, fixed_point<Ib,Db> b) { return recast(Ia+Da+Db, a.v) * b.factor == recast(Ib+Db+Da, b.v) * a.factor; }
template<int Ia, int Da, int Ib, int Db> bool operator!= (fixed_point<Ia,Da> a, fixed_point<Ib,Db> b) { return recast(Ia+Da+Db, a.v) * b.factor != recast(Ib+Db+Da, b.v) * a.factor; }

template<typename R, int Ia, int Da> bool operator>  (R r, fixed_point<Ia,Da> f) { return r * recast(Ia+Da+Da, f.factor) >  f.v; }
template<typename R, int Ia, int Da> bool operator<  (R r, fixed_point<Ia,Da> f) { return r * recast(Ia+Da+Da, f.factor) <  f.v; }
template<typename R, int Ia, int Da> bool operator>= (R r, fixed_point<Ia,Da> f) { return r * recast(Ia+Da+Da, f.factor) >= f.v; }
template<typename R, int Ia, int Da> bool operator<= (R r, fixed_point<Ia,Da> f) { return r * recast(Ia+Da+Da, f.factor) <= f.v; }
template<typename R, int Ia, int Da> bool operator== (R r, fixed_point<Ia,Da> f) { return r * recast(Ia+Da+Da, f.factor) == f.v; }
template<typename R, int Ia, int Da> bool operator!= (R r, fixed_point<Ia,Da> f) { return r * recast(Ia+Da+Da, f.factor) != f.v; }

template<typename R, int Ia, int Da> bool operator>  (fixed_point<Ia,Da> f, R r) { return f.v >  r * recast(Ia+Da+Da, f.factor); }
template<typename R, int Ia, int Da> bool operator<  (fixed_point<Ia,Da> f, R r) { return f.v <  r * recast(Ia+Da+Da, f.factor); }
template<typename R, int Ia, int Da> bool operator>= (fixed_point<Ia,Da> f, R r) { return f.v >= r * recast(Ia+Da+Da, f.factor); }
template<typename R, int Ia, int Da> bool operator<= (fixed_point<Ia,Da> f, R r) { return f.v <= r * recast(Ia+Da+Da, f.factor); }
template<typename R, int Ia, int Da> bool operator== (fixed_point<Ia,Da> f, R r) { return f.v == r * recast(Ia+Da+Da, f.factor); }
template<typename R, int Ia, int Da> bool operator!= (fixed_point<Ia,Da> f, R r) { return f.v != r * recast(Ia+Da+Da, f.factor); }

#undef recast

} // namespace gamma