/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include <ostream>
#define GAMMA_HAS_STREAM

namespace gamma {

#ifdef GAMMA_HAS_VECTOR
template<typename T> std::ostream& operator<< (std::ostream& o, const vector2<T>& v) { o << v.x << ' ' << v.y; return o; }
template<typename T> std::ostream& operator<< (std::ostream& o, const vector3<T>& v) { o << v.x << ' ' << v.y << ' ' << v.z; return o; }
template<typename T> std::ostream& operator<< (std::ostream& o, const vector4<T>& v) { o << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w; return o; }
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

} // namespace gamma
