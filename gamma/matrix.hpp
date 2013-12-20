/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "vector.hpp"

namespace gamma {

#define matrix2_comp_comma(op, h) m00 op h.m00, m10 op h.m10, m01 op h.m01, m11 op h.m11
#define matrix2_comp_semi(op, h) m00 op h.m00; m10 op h.m10; m01 op h.m01; m11 op h.m11
#define matrix2_comp_comma_scalar(op, h) m00 op h, m10 op h, m01 op h, m11 op h
#define matrix2_comp_semi_scalar(op, h) m00 op h; m10 op h; m01 op h; m11 op h

/// 2x2 column-major matrix.
template <typename T> struct matrix2
{
	typedef T type;
	typedef matrix2<T> self;
	typedef vector2<T> column;

	union {
		struct { T m00, m10, m01, m11; };
		T v[4];
		T a[2][2];
	};

	matrix2() {}
	explicit matrix2(T d) : m00(d), m01(0), m10(0), m11(d) {}
	explicit matrix2(const column& c0, const column& c1) : m00(c0.x), m10(c0.y), m01(c1.x), m11(c1.y) {}
	explicit matrix2(T m00, T m01, T m10, T m11) : m00(m00), m01(m01), m10(m10), m11(m11) {}
	template<typename R> explicit matrix2(const matrix2<R>& h) : m00(h.m00), m10(h.m10), m01(h.m01), m11(h.m11) {}

	template<typename R> operator matrix2<R>() const { return matrix2<R>(*this); }
	T& operator() (int row, int column) { return a[column][row]; }
	T operator() (int row, int column) const { return a[column][row]; }
	column operator() (int column) const { return column(a[column][0], a[column][1]); }

	self operator- () const { return self(-m00, -m01, -m10, -m11); }
	template<typename R> self& operator= (const matrix2<R>& h) { m00=h.m00; m01=h.m01; m10=h.m10; m11=h.m11; return *this; }

	template<typename R> self mul(const matrix2<R>& h) const { return self(m00*h.m00, m01*h.m01, m10*h.m10, m11*h.m11); }
	template<typename R> self div(const matrix2<R>& h) const { return self(m00/h.m00, m01/h.m01, m10/h.m10, m11/h.m11); }

	template<typename R> self& operator+= (const vector2<R>& h) { m00+=h.m00; m01+=h.m01; m10+=h.m10; m11+=h.m11; return *this; }
	template<typename R> self& operator-= (const vector2<R>& h) { m00-=h.m00; m01-=h.m01; m10-=h.m10; m11-=h.m11; return *this; }
	template<typename R> self& muleq(const vector2<R>& h) { m00*=h.m00; m01*=h.m01; m10*=h.m10; m11*=h.m11; return *this; }
	template<typename R> self& diveq(const vector2<R>& h) { m00/=h.m00; m01/=h.m01; m10/=h.m10; m11/=h.m11; return *this; }

	template<typename R> self& operator+= (R h) { m00+=h; m01+=h; m10+=h; m11+=h; return *this; }
	template<typename R> self& operator-= (R h) { m00-=h; m01-=h; m10-=h; m11-=h; return *this; }
	template<typename R> self& operator*= (R h) { m00*=h; m01*=h; m10*=h; m11*=h; return *this; }
	template<typename R> self& operator/= (R h) { m00/=h; m01/=h; m10/=h; m11/=h; return *this; }

	template<typename R> self& operator*= (const matrix2<R>& h) const {	return *this = *this * h; }
};

template<typename T, typename R> matrix2<T> operator+ (const matrix2<T>& v, const matrix2<R>& h) { return matrix2<T>(v.m00+h.m00, v.m01+h.m01, v.m10+h.m10, v.m11+h.m11); }
template<typename T, typename R> matrix2<T> operator- (const matrix2<T>& v, const matrix2<R>& h) { return matrix2<T>(v.m00-h.m00, v.m01-h.m01, v.m10-h.m10, v.m11-h.m11); }
template<typename T, typename R> matrix2<T> operator* (const matrix2<T>& v, const matrix2<R>& h) { return self(
	v.m00*h.m01 + v.m01*h.m11, // m01
	v.m00*h.m00 + v.m01*h.m10, // m00

	v.m10*h.m00 + v.m11*h.m10, // m10
	v.m10*h.m01 + v.m11*h.m11  // m11
); }
template<typename T, typename R> vector2<R> operator* (const matrix2<T>& v, const vector2<R>& h) { return vector2<R>(
	v.m00*h.x + v.m01*h.y, // x
	v.m10*h.x + v.m11*h.y  // y
); }

template<typename T, typename R> matrix2<T> operator+ (R h, const matrix2<T>& v) { return matrix2<T>(h+v.m00, h+v.m01, h+v.m10, h+v.m11); }
template<typename T, typename R> matrix2<T> operator- (R h, const matrix2<T>& v) { return matrix2<T>(h-v.m00, h-v.m01, h-v.m10, h-v.m11); }
template<typename T, typename R> matrix2<T> operator* (R h, const matrix2<T>& v) { return matrix2<T>(h*v.m00, h*v.m01, h*v.m10, h*v.m11); }
template<typename T, typename R> matrix2<T> operator/ (R h, const matrix2<T>& v) { return matrix2<T>(h/v.m00, h/v.m01, h/v.m10, h/v.m11); }

template<typename T, typename R> matrix2<T> operator+ (const matrix2<T>& v, R h) { return matrix2<T>(v.m00+h, v.m01+h, v.m10+h, v.m11+h); }
template<typename T, typename R> matrix2<T> operator- (const matrix2<T>& v, R h) { return matrix2<T>(v.m00-h, v.m01-h, v.m10-h, v.m11-h); }
template<typename T, typename R> matrix2<T> operator* (const matrix2<T>& v, R h) { return matrix2<T>(v.m00*h, v.m01*h, v.m10*h, v.m11*h); }
template<typename T, typename R> matrix2<T> operator/ (const matrix2<T>& v, R h) { return matrix2<T>(v.m00/h, v.m01/h, v.m10/h, v.m11/h); }


/// 3x3 column-major matrix.
template <typename T> struct matrix3
{
	typedef T type;
	typedef matrix3<T> self;
	typedef vector3<T> column;

	union {
		struct { T m00,m10,m20, m01,m11,m21, m02,m12,m22; };
		T v[9];
		T a[3][3];
	};

	matrix3() {}
	explicit matrix3(T d):
		m00(d), m01(0), m02(0),
		m10(0), m11(d), m12(0),
		m20(0), m21(0), m22(d) {}
	explicit matrix3(const column& c0, const column& c1, const column& c2):
		m00(c0.x), m10(c0.y), m20(c0.z),
		m01(c1.x), m11(c1.y), m21(c1.z),
		m02(c2.x), m12(c2.y), m22(c2.z) {}
	explicit matrix3(
		T m00, T m01, T m02,
		T m10, T m11, T m12,
		T m20, T m21, T m22):
		m00(m00), m01(m01), m02(m02),
		m10(m10), m11(m11), m12(m12),
		m20(m20), m21(m21), m22(m22) {}
	template<typename R> explicit matrix3(const matrix3<R>& h):
		m00(h.m00), m01(h.m01), m02(h.m02),
		m10(h.m10), m11(h.m11), m12(h.m12),
		m20(h.m20), m21(h.m21), m22(h.m22) {}

	template<typename R> operator matrix3<R>() const { return matrix3<R>(*this); }
	T& operator() (int row, int column) { return a[column][row]; }
	T operator() (int row, int column) const { return a[column][row]; }
	column operator() (int column) const { return column(a[column][0], a[column][1], a[column][2]); }

	self operator- () const { return self(
		-m00, -m01, -m02,
		-m10, -m11, -m12,
		-m20, -m21, -m22); }
	template<typename R> self& operator= (const matrix3<R>& h) {
		m00=h.m00; m01=h.m01; m02=h.m02;
		m10=h.m10; m11=h.m11; m12=h.m12;
		m20=h.m20; m21=h.m21; m22=h.m22;
		return *this; }

	template<typename R> self mul(const matrix3<R>& h) const { return self(
		m00*h.m00, m01*h.m01, m02*h.m02,
		m10*h.m10, m11*h.m11, m12*h.m12,
		m20*h.m20, m21*h.m21, m22*h.m22); }
	template<typename R> self div(const matrix3<R>& h) const { return self(
		m00/h.m00, m01/h.m01, m02/h.m02,
		m10/h.m10, m11/h.m11, m12/h.m12,
		m20/h.m20, m21/h.m21, m22/h.m22); }

	template<typename R> self& operator+= (const vector3<R>& h) {
		m00+=h.m00; m01+=h.m01; m02+=h.m02;
		m10+=h.m10; m11+=h.m11; m12+=h.m12;
		m20+=h.m20; m21+=h.m21; m22+=h.m22;
		return *this; }
	template<typename R> self& operator-= (const vector3<R>& h) {
		m00+=h.m00; m01-=h.m01; m02-=h.m02;
		m10-=h.m10; m11-=h.m11; m12-=h.m12;
		m20-=h.m20; m21-=h.m21; m22-=h.m22;
		return *this; }
	template<typename R> self& muleq(const vector3<R>& h) {
		m00*=h.m00; m01*=h.m01; m02*=h.m02;
		m10*=h.m10; m11*=h.m11; m12*=h.m12;
		m20*=h.m20; m21*=h.m21; m22*=h.m22;
		return *this; }
	template<typename R> self& diveq(const vector3<R>& h) {
		m00/=h.m00; m01/=h.m01; m02/=h.m02;
		m10/=h.m10; m11/=h.m11; m12/=h.m12;
		m20/=h.m20; m21/=h.m21; m22/=h.m22;
		return *this; }

	template<typename R> self& operator+= (R h) {
		m00+=h; m01+=h; m02+=h;
		m10+=h; m11+=h; m12+=h;
		m20+=h; m21+=h; m22+=h;
		return *this; }
	template<typename R> self& operator-= (R h) {
		m00-=h; m01-=h; m02-=h;
		m10-=h; m11-=h; m12-=h;
		m20-=h; m21-=h; m22-=h;
		return *this; }
	template<typename R> self& operator*= (R h) {
		m00*=h; m01*=h; m02*=h;
		m10*=h; m11*=h; m12*=h;
		m20*=h; m21*=h; m22*=h;
		return *this; }
	template<typename R> self& operator/= (R h) {
		m00/=h; m01/=h; m02/=h;
		m10/=h; m11/=h; m12/=h;
		m20/=h; m21/=h; m22/=h;
		return *this; }

	template<typename R> self& operator*= (const matrix3<R>& h) const {	return *this = *this * h; }
};

template<typename T, typename R> matrix3<T> operator+ (const matrix3<T>& v, const matrix3<R>& h) { return matrix3<T>(
	v.m00+h.m00, v.m01+h.m01, v.m02+h.m02,
	v.m10+h.m10, v.m11+h.m11, v.m12+h.m12,
	v.m20+h.m20, v.m21+h.m21, v.m22+h.m22); }
template<typename T, typename R> matrix3<T> operator- (const matrix3<T>& v, const matrix3<R>& h) { return matrix3<T>(
	v.m00-h.m00, v.m01-h.m01, v.m02-h.m02,
	v.m10-h.m10, v.m11-h.m11, v.m12-h.m12,
	v.m20-h.m20, v.m21-h.m21, v.m22-h.m22); }
template<typename T, typename R> matrix3<T> operator* (const matrix3<T>& v, const matrix3<R>& h) { return self(
	v.m00*h.m00 + v.m01*h.m10 + v.m02*h.m20, // m00
	v.m00*h.m01 + v.m01*h.m11 + v.m02*h.m21, // m01
	v.m00*h.m02 + v.m01*h.m12 + v.m02*h.m22, // m02

	v.m10*h.m00 + v.m11*h.m10 + v.m12*h.m20, // m10
	v.m10*h.m01 + v.m11*h.m11 + v.m12*h.m21, // m11
	v.m10*h.m02 + v.m11*h.m12 + v.m12*h.m22, // m12

	v.m20*h.m00 + v.m21*h.m10 + v.m22*h.m20, // m20
	v.m20*h.m01 + v.m21*h.m11 + v.m22*h.m21, // m21
	v.m20*h.m02 + v.m21*h.m12 + v.m22*h.m22  // m22
); }
template<typename T, typename R> vector3<R> operator* (const matrix3<T>& v, const vector3<R>& h) { return vector3<R>(
	v.m00*h.x + v.m01*h.y + v.m02*h.z, // x
	v.m10*h.x + v.m11*h.y + v.m12*h.z, // y
	v.m20*h.x + v.m21*h.y + v.m22*h.z  // z
); }

template<typename T, typename R> matrix3<T> operator+ (R h, const matrix3<T>& v) { return matrix3<T>(
	h+v.m00, h+v.m01, h+v.m02,
	h+v.m10, h+v.m11, h+v.m12,
	h+v.m20, h+v.m21, h+v.m22); }
template<typename T, typename R> matrix3<T> operator- (R h, const matrix3<T>& v) { return matrix3<T>(
	h-v.m00, h-v.m01, h-v.m02,
	h-v.m10, h-v.m11, h-v.m12,
	h-v.m20, h-v.m21, h-v.m22); }
template<typename T, typename R> matrix3<T> operator* (R h, const matrix3<T>& v) { return matrix3<T>(
	h*v.m00, h*v.m01, h*v.m02,
	h*v.m10, h*v.m11, h*v.m12,
	h*v.m20, h*v.m21, h*v.m22); }
template<typename T, typename R> matrix3<T> operator/ (R h, const matrix3<T>& v) { return matrix3<T>(
	h/v.m00, h/v.m01, h/v.m02,
	h/v.m10, h/v.m11, h/v.m12,
	h/v.m20, h/v.m21, h/v.m22); }

template<typename T, typename R> matrix3<T> operator+ (const matrix3<T>& v, R h) { return matrix3<T>(
	v.m00+h, v.m01+h, v.m02+h,
	v.m10+h, v.m11+h, v.m12+h,
	v.m20+h, v.m21+h, v.m22+h); }
template<typename T, typename R> matrix3<T> operator- (const matrix3<T>& v, R h) { return matrix3<T>(
	v.m00-h, v.m01-h, v.m02-h,
	v.m10-h, v.m11-h, v.m12-h,
	v.m20-h, v.m21-h, v.m22-h); }
template<typename T, typename R> matrix3<T> operator* (const matrix3<T>& v, R h) { return matrix3<T>(
	v.m00*h, v.m01*h, v.m02*h,
	v.m10*h, v.m11*h, v.m12*h,
	v.m20*h, v.m21*h, v.m22*h); }
template<typename T, typename R> matrix3<T> operator/ (const matrix3<T>& v, R h) { return matrix3<T>(
	v.m00/h, v.m01/h, v.m02/h,
	v.m10/h, v.m11/h, v.m12/h,
	v.m20/h, v.m21/h, v.m22/h); }


/// 4x4 column-major matrix.
template <typename T> struct matrix4
{
	typedef T type;
	typedef matrix4<T> self;
	typedef vector4<T> column;

	union {
		struct { T m00,m10,m20,m30, m01,m11,m21,m31, m02,m12,m22,m32, m03,m13,m23,m33; };
		T v[16];
		T a[4][4];
	};

	matrix4() {}
	explicit matrix4(T d):
		m00(d), m01(0), m02(0), m03(0),
		m10(0), m11(d), m12(0), m13(0),
		m20(0), m21(0), m22(d), m23(0),
		m30(0), m31(0), m32(0), m33(d) {}
	explicit matrix4(const column& c0, const column& c1, const column& c2, const column& c3):
		m00(c0.x), m10(c0.y), m20(c0.z), m30(c0.w),
		m01(c1.x), m11(c1.y), m21(c1.z), m31(c1.w),
		m02(c2.x), m12(c2.y), m22(c2.z), m32(c2.w),
		m03(c3.x), m13(c3.y), m23(c3.z), m33(c3.w) {}
	explicit matrix4(
		T m00, T m01, T m02, T m03,
		T m10, T m11, T m12, T m13,
		T m20, T m21, T m22, T m23,
		T m30, T m31, T m32, T m33):
		m00(m00), m01(m01), m02(m02), m03(m03),
		m10(m10), m11(m11), m12(m12), m13(m13),
		m20(m20), m21(m21), m22(m22), m23(m23),
		m30(m30), m31(m31), m32(m32), m33(m33) {}
	template<typename R> explicit matrix4(const matrix4<R>& h):
		m00(h.m00), m01(h.m01), m02(h.m02), m03(h.m03),
		m10(h.m10), m11(h.m11), m12(h.m12), m13(h.m13),
		m20(h.m20), m21(h.m21), m22(h.m22), m23(h.m23),
		m30(h.m30), m31(h.m31), m32(h.m32), m33(h.m33) {}

	template<typename R> operator matrix4<R>() const { return matrix4<R>(*this); }
	T& operator() (int row, int column) { return a[column][row]; }
	T operator() (int row, int column) const { return a[column][row]; }
	column operator() (int column) const { return column(a[column][0], a[column][1], a[column][2], a[column][3]); }

	self operator- () const { return self(
		-m00, -m01, -m02, -m03,
		-m10, -m11, -m12, -m13,
		-m20, -m21, -m22, -m23,
		-m30, -m31, -m32, -m33); }
	template<typename R> self& operator= (const matrix4<R>& h) {
		m00=h.m00; m01=h.m01; m02=h.m02; m03=h.m03;
		m10=h.m10; m11=h.m11; m12=h.m12; m13=h.m13;
		m20=h.m20; m21=h.m21; m22=h.m22; m23=h.m23;
		m30=h.m30; m31=h.m31; m32=h.m32; m33=h.m33;
		return *this; }

	template<typename R> self mul(const matrix4<R>& h) const { return self(
		m00*h.m00, m01*h.m01, m02*h.m02, m03*h.m03,
		m10*h.m10, m11*h.m11, m12*h.m12, m13*h.m13,
		m20*h.m20, m21*h.m21, m22*h.m22, m23*h.m23,
		m30*h.m30, m31*h.m31, m32*h.m32, m33*h.m33); }
	template<typename R> self div(const matrix4<R>& h) const { return self(
		m00/h.m00, m01/h.m01, m02/h.m02, m03/h.m03,
		m10/h.m10, m11/h.m11, m12/h.m12, m13/h.m13,
		m20/h.m20, m21/h.m21, m22/h.m22, m23/h.m23,
		m30/h.m30, m31/h.m31, m32/h.m32, m33/h.m33); }

	template<typename R> self& operator+= (const vector4<R>& h) {
		m00+=h.m00; m01+=h.m01; m02+=h.m02; m03+=h.m03;
		m10+=h.m10; m11+=h.m11; m12+=h.m12; m13+=h.m13;
		m20+=h.m20; m21+=h.m21; m22+=h.m22; m23+=h.m23;
		m30+=h.m30; m31+=h.m31; m32+=h.m32; m33+=h.m33;
		return *this; }
	template<typename R> self& operator-= (const vector4<R>& h) {
		m00+=h.m00; m01-=h.m01; m02-=h.m02; m03-=h.m03;
		m10-=h.m10; m11-=h.m11; m12-=h.m12; m13-=h.m13;
		m20-=h.m20; m21-=h.m21; m22-=h.m22; m23-=h.m23;
		m30-=h.m30; m31-=h.m31; m32-=h.m32; m33-=h.m33;
		return *this; }
	template<typename R> self& muleq(const vector4<R>& h) {
		m00*=h.m00; m01*=h.m01; m02*=h.m02; m03*=h.m03;
		m10*=h.m10; m11*=h.m11; m12*=h.m12; m13*=h.m13;
		m20*=h.m20; m21*=h.m21; m22*=h.m22; m23*=h.m23;
		m30*=h.m30; m31*=h.m31; m32*=h.m32; m33*=h.m33;
		return *this; }
	template<typename R> self& diveq(const vector4<R>& h) {
		m00/=h.m00; m01/=h.m01; m02/=h.m02; m03/=h.m03;
		m10/=h.m10; m11/=h.m11; m12/=h.m12; m13/=h.m13;
		m20/=h.m20; m21/=h.m21; m22/=h.m22; m23/=h.m23;
		m30/=h.m30; m31/=h.m31; m32/=h.m32; m33/=h.m33;
		return *this; }

	template<typename R> self& operator+= (R h) {
		m00+=h; m01+=h; m02+=h; m03+=h;
		m10+=h; m11+=h; m12+=h; m13+=h;
		m20+=h; m21+=h; m22+=h; m23+=h;
		m30+=h; m31+=h; m32+=h; m33+=h;
		return *this; }
	template<typename R> self& operator-= (R h) {
		m00-=h; m01-=h; m02-=h; m03-=h;
		m10-=h; m11-=h; m12-=h; m13-=h;
		m20-=h; m21-=h; m22-=h; m23-=h;
		m30-=h; m31-=h; m32-=h; m33-=h;
		return *this; }
	template<typename R> self& operator*= (R h) {
		m00*=h; m01*=h; m02*=h; m03*=h;
		m10*=h; m11*=h; m12*=h; m13*=h;
		m20*=h; m21*=h; m22*=h; m23*=h;
		m30*=h; m31*=h; m32*=h; m33*=h;
		return *this; }
	template<typename R> self& operator/= (R h) {
		m00/=h; m01/=h; m02/=h; m03/=h;
		m10/=h; m11/=h; m12/=h; m13/=h;
		m20/=h; m21/=h; m22/=h; m23/=h;
		m30/=h; m31/=h; m22/=h; m23/=h;
		return *this; }

	template<typename R> self& operator*= (const matrix4<R>& h) const {	return *this = *this * h; }
};

template<typename T, typename R> matrix4<T> operator+ (const matrix4<T>& v, const matrix4<R>& h) { return matrix4<T>(
	v.m00+h.m00, v.m01+h.m01, v.m02+h.m02, v.m03+h.m03,
	v.m10+h.m10, v.m11+h.m11, v.m12+h.m12, v.m13+h.m13,
	v.m20+h.m20, v.m21+h.m21, v.m22+h.m22, v.m23+h.m23,
	v.m30+h.m30, v.m31+h.m31, v.m32+h.m32, v.m33+h.m33); }
template<typename T, typename R> matrix4<T> operator- (const matrix4<T>& v, const matrix4<R>& h) { return matrix4<T>(
	v.m00-h.m00, v.m01-h.m01, v.m02-h.m02, v.m03-h.m03,
	v.m10-h.m10, v.m11-h.m11, v.m12-h.m12, v.m13-h.m13,
	v.m20-h.m20, v.m21-h.m21, v.m22-h.m22, v.m23-h.m23,
	v.m30-h.m30, v.m31-h.m31, v.m32-h.m32, v.m33-h.m33); }
template<typename T, typename R> matrix4<T> operator* (const matrix4<T>& v, const matrix4<R>& h) { return self(
	v.m00*h.m00 + v.m01*h.m10 + v.m02*h.m20 + v.m03*h.m30, // m00
	v.m00*h.m01 + v.m01*h.m11 + v.m02*h.m21 + v.m03*h.m31, // m01
	v.m00*h.m02 + v.m01*h.m12 + v.m02*h.m22 + v.m03*h.m32, // m02
	v.m00*h.m03 + v.m01*h.m13 + v.m02*h.m23 + v.m03*h.m33, // m03

	v.m10*h.m00 + v.m11*h.m10 + v.m12*h.m20 + v.m13*h.m30, // m10
	v.m10*h.m01 + v.m11*h.m11 + v.m12*h.m21 + v.m13*h.m31, // m11
	v.m10*h.m02 + v.m11*h.m12 + v.m12*h.m22 + v.m13*h.m32, // m12
	v.m10*h.m03 + v.m11*h.m13 + v.m12*h.m23 + v.m13*h.m33, // m13

	v.m20*h.m00 + v.m21*h.m10 + v.m22*h.m20 + v.m23*h.m30, // m20
	v.m20*h.m01 + v.m21*h.m11 + v.m22*h.m21 + v.m23*h.m31, // m21
	v.m20*h.m02 + v.m21*h.m12 + v.m22*h.m22 + v.m23*h.m32, // m22
	v.m20*h.m03 + v.m21*h.m13 + v.m22*h.m23 + v.m23*h.m33, // m23

	v.m30*h.m00 + v.m31*h.m10 + v.m32*h.m20 + v.m33*h.m30, // m30
	v.m30*h.m01 + v.m31*h.m11 + v.m32*h.m21 + v.m33*h.m31, // m31
	v.m30*h.m02 + v.m31*h.m12 + v.m32*h.m22 + v.m33*h.m32, // m32
	v.m30*h.m03 + v.m31*h.m13 + v.m32*h.m23 + v.m33*h.m33  // m33
); }
template<typename T, typename R> vector4<R> operator* (const matrix4<T>& v, const vector4<R>& h) { return vector4<R>(
	v.m00*h.x + v.m01*h.y + v.m02*h.z + v.m03*h.w, // x
	v.m10*h.x + v.m11*h.y + v.m12*h.z + v.m13*h.w, // y
	v.m20*h.x + v.m21*h.y + v.m22*h.z + v.m23*h.w, // z
	v.m30*h.x + v.m31*h.y + v.m32*h.z + v.m33*h.w  // w
); }

template<typename T, typename R> matrix4<T> operator+ (R h, const matrix4<T>& v) { return matrix4<T>(
	h+v.m00, h+v.m01, h+v.m02, h+v.m03,
	h+v.m10, h+v.m11, h+v.m12, h+v.m13,
	h+v.m20, h+v.m21, h+v.m22, h+v.m23,
	h+v.m30, h+v.m31, h+v.m32, h+v.m33); }
template<typename T, typename R> matrix4<T> operator- (R h, const matrix4<T>& v) { return matrix4<T>(
	h-v.m00, h-v.m01, h-v.m02, h-v.m03,
	h-v.m10, h-v.m11, h-v.m12, h-v.m13,
	h-v.m20, h-v.m21, h-v.m22, h-v.m23,
	h-v.m30, h-v.m31, h-v.m32, h-v.m33); }
template<typename T, typename R> matrix4<T> operator* (R h, const matrix4<T>& v) { return matrix4<T>(
	h*v.m00, h*v.m01, h*v.m02, h*v.m03,
	h*v.m10, h*v.m11, h*v.m12, h*v.m13,
	h*v.m20, h*v.m21, h*v.m22, h*v.m23,
	h*v.m30, h*v.m31, h*v.m32, h*v.m33); }
template<typename T, typename R> matrix4<T> operator/ (R h, const matrix4<T>& v) { return matrix4<T>(
	h/v.m00, h/v.m01, h/v.m02, h/v.m03,
	h/v.m10, h/v.m11, h/v.m12, h/v.m13,
	h/v.m20, h/v.m21, h/v.m22, h/v.m23,
	h/v.m30, h/v.m31, h/v.m32, h/v.m33); }

template<typename T, typename R> matrix4<T> operator+ (const matrix4<T>& v, R h) { return matrix4<T>(
	v.m00+h, v.m01+h, v.m02+h, v.m03+h,
	v.m10+h, v.m11+h, v.m12+h, v.m13+h,
	v.m20+h, v.m21+h, v.m22+h, v.m23+h,
	v.m30+h, v.m31+h, v.m32+h, v.m33+h); }
template<typename T, typename R> matrix4<T> operator- (const matrix4<T>& v, R h) { return matrix4<T>(
	v.m00-h, v.m01-h, v.m02-h, v.m03-h,
	v.m10-h, v.m11-h, v.m12-h, v.m13-h,
	v.m20-h, v.m21-h, v.m22-h, v.m23-h,
	v.m30-h, v.m31-h, v.m32-h, v.m33-h); }
template<typename T, typename R> matrix4<T> operator* (const matrix4<T>& v, R h) { return matrix4<T>(
	v.m00*h, v.m01*h, v.m02*h, v.m03*h,
	v.m10*h, v.m11*h, v.m12*h, v.m13*h,
	v.m20*h, v.m21*h, v.m22*h, v.m23*h,
	v.m30*h, v.m31*h, v.m32*h, v.m33*h); }
template<typename T, typename R> matrix4<T> operator/ (const matrix4<T>& v, R h) { return matrix4<T>(
	v.m00/h, v.m01/h, v.m02/h, v.m03/h,
	v.m10/h, v.m11/h, v.m12/h, v.m13/h,
	v.m20/h, v.m21/h, v.m22/h, v.m23/h,
	v.m30/h, v.m31/h, v.m32/h, v.m33/h); }


namespace convenience {
	typedef matrix2<uint8_t> matrix2b;
	typedef matrix3<uint8_t> matrix3b;
	typedef matrix4<uint8_t> matrix4b;

	typedef matrix2<int> matrix2i;
	typedef matrix3<int> matrix3i;
	typedef matrix4<int> matrix4i;

	typedef matrix2<float> matrix2f;
	typedef matrix3<float> matrix3f;
	typedef matrix4<float> matrix4f;
	
	typedef matrix2<double> matrix2d;
	typedef matrix3<double> matrix3d;
	typedef matrix4<double> matrix4d;
}
} // namespace gamma