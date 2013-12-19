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

} // namespace gamma
