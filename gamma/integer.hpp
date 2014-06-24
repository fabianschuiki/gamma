/* Copyright (c) 2013-2014 Fabian Schuiki */
#pragma once
#include "gamma/math.hpp"
#define GAMMA_HAS_INTEGER

namespace gma {
namespace integer {

template <int N> struct signed_integer : public signed_integer<N+1> { const static int requested_bits = N; };
template <int N> struct unsigned_integer : public unsigned_integer<N+1> { const static int requested_bits = N; };

#define declare_integer(base, storage_type) template<> struct base<sizeof(storage_type)*8> { const static int bits = sizeof(storage_type)*8; const static int requested_bits = bits; typedef storage_type type; };
#define declare_signed_integer(storage_type) declare_integer(signed_integer, storage_type)
#define declare_unsigned_integer(storage_type) declare_integer(unsigned_integer, storage_type)

declare_signed_integer(int8_t)
declare_signed_integer(int16_t)
declare_signed_integer(int32_t)
declare_signed_integer(int64_t)

declare_unsigned_integer(uint8_t)
declare_unsigned_integer(uint16_t)
declare_unsigned_integer(uint32_t)
declare_unsigned_integer(uint64_t)

#undef declare_integer
#undef declare_signed_integer
#undef declare_unsigned_integer

} // namespace integer
} // namespace gma
