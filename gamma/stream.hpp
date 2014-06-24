/* Copyright (c) 2013-2014 Fabian Schuiki */
#pragma once
#include <ostream>
#define GAMMA_HAS_STREAM

namespace gma {

#ifdef GAMMA_HAS_VECTOR
template<typename T> std::ostream& operator<< (std::ostream& o, const vector2<T>& v) { o << v.x << ' ' << v.y; return o; }
template<typename T> std::ostream& operator<< (std::ostream& o, const vector3<T>& v) { o << v.x << ' ' << v.y << ' ' << v.z; return o; }
template<typename T> std::ostream& operator<< (std::ostream& o, const vector4<T>& v) { o << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w; return o; }
#endif

#ifdef GAMMA_HAS_MATRIX
template<typename T> std::ostream& operator<< (std::ostream& o, const matrix2<T>& m) {
	o << m.m00 << ' ' << m.m01 << '\n';
	o << m.m10 << ' ' << m.m11; return o;
}
template<typename T> std::ostream& operator<< (std::ostream& o, const matrix3<T>& m) {
	o << m.m00 << ' ' << m.m01 << ' ' << m.m02 << '\n';
	o << m.m10 << ' ' << m.m11 << ' ' << m.m12 << '\n';
	o << m.m20 << ' ' << m.m21 << ' ' << m.m22; return o;
}
template<typename T> std::ostream& operator<< (std::ostream& o, const matrix4<T>& m) {
	o << m.m00 << ' ' << m.m01 << ' ' << m.m02 << ' ' << m.m03 << '\n';
	o << m.m10 << ' ' << m.m11 << ' ' << m.m12 << ' ' << m.m13 << '\n';
	o << m.m20 << ' ' << m.m21 << ' ' << m.m22 << ' ' << m.m23 << '\n';
	o << m.m30 << ' ' << m.m31 << ' ' << m.m32 << ' ' << m.m33; return o;
}
#endif

#ifdef GAMMA_HAS_SPHERE
template<typename T> std::ostream& operator<< (std::ostream& o, const sphere<T>& s) { o << '(' << s.c << ", " << s.r << ')'; return o; }
#endif

#ifdef GAMMA_HAS_LINE
template<typename T> std::ostream& operator<< (std::ostream& o, const line<T>& l) { o << '(' << s.p << ", " << s.d << ')'; return o; }
#endif

#ifdef GAMMA_HAS_FIXED_POINT
template<int Ia, int Ib> std::ostream& operator<< (std::ostream& o, fixed_point<Ia,Ib> f) { o << (double)f.v / f.factor; return o; }
#endif

} // namespace gma
