/* Copyright (c) 2013 Fabian Schuiki */
#define BOOST_TEST_MODULE gamma
#include <gamma/integer.hpp>
#include <gamma/vector.hpp>
#include <gamma/matrix.hpp>
#include <gamma/fixed_point.hpp>
#include <gamma/transform/translation.hpp>
#include <gamma/transform/x_rotation.hpp>
#include <gamma/transform/y_rotation.hpp>
#include <gamma/transform/z_rotation.hpp>
#include <gamma/transform/axial_rotation.hpp>
#include <gamma/transform/perspective.hpp>
#include <gamma/transform/orientation.hpp>
#include <gamma/transform/lookat.hpp>
#include <gamma/mvp.hpp>
#include <boost/test/unit_test.hpp>

using namespace gamma::convenience;

BOOST_AUTO_TEST_CASE(integer)
{
	#define check(_type, _bits, _target)\
		BOOST_CHECK_EQUAL((int)(gamma::integer::_type<_bits>::requested_bits), _bits);\
		BOOST_CHECK_EQUAL((int)(gamma::integer::_type<_bits>::bits), _target*8);\
		BOOST_CHECK_EQUAL(sizeof(gamma::integer::_type<_bits>::type), _target);

	#define check_pair(bits, target)\
		check(signed_integer, bits, target);\
		check(unsigned_integer, bits, target);

	#define check_eight(bits, target)\
		check_pair(bits+1, target);\
		check_pair(bits+2, target);\
		check_pair(bits+3, target);\
		check_pair(bits+4, target);\
		check_pair(bits+5, target);\
		check_pair(bits+6, target);\
		check_pair(bits+7, target);\
		check_pair(bits+8, target);

	check_eight(0, 1);
	check_eight(8, 2);
	check_eight(16, 4);
	check_eight(24, 4);
	check_eight(32, 8);
	check_eight(40, 8);
	check_eight(48, 8);
	check_eight(56, 8);

	#undef check
	#undef check_pair
	#undef check_eight
}

BOOST_AUTO_TEST_CASE(sizes)
{
	#define check(type, target) BOOST_CHECK_EQUAL(sizeof(type), target)

	#define check_vector(dim)\
		check(vector ## dim ## b, 1*dim);\
		check(vector ## dim ## i, 4*dim);\
		check(vector ## dim ## f, 4*dim);\
		check(vector ## dim ## d, 8*dim);

	#define check_matrix(dim)\
		check(matrix ## dim ## b, 1*dim*dim);\
		check(matrix ## dim ## i, 4*dim*dim);\
		check(matrix ## dim ## f, 4*dim*dim);\
		check(matrix ## dim ## d, 8*dim*dim);

	check_vector(2);
	check_vector(3);
	check_vector(4);

	check_matrix(2);
	check_matrix(3);
	check_matrix(4);

	#undef check
	#undef check_vector
	#undef check_matrix
}

BOOST_AUTO_TEST_CASE(matrix_column_major)
{
	#define verify_column_major(type, dim) {\
		type m;\
		m.m10 = 1;\
		m.m01 = 2;\
		BOOST_CHECK(m.a[0][1] == 1 && m.a[1][0] == 2);\
	}

	#define verify_column_major_matrices(dim)\
		verify_column_major(matrix ## dim ## b, dim);\
		verify_column_major(matrix ## dim ## i, dim);\
		verify_column_major(matrix ## dim ## f, dim);\
		verify_column_major(matrix ## dim ## d, dim);

	verify_column_major_matrices(2);
	verify_column_major_matrices(3);
	verify_column_major_matrices(4);

	#undef verify_column_major
	#undef verify_column_major_matrices
}

/** This test tries to trigger an overflow of a fixed_point's underlying
 * storage by multiplying two large numbers. */
BOOST_AUTO_TEST_CASE(fixed_point_overflow)
{
	gamma::fixed_point<24,8> a0, a1, a2;
	a0.v = 0x00008000;
	a1.v = 0x00010000;
	a2.v = 0x0007ff00;

	BOOST_CHECK_EQUAL((a0*a0).v, 0x80*0x80 * 0x100);
	BOOST_CHECK_EQUAL((a1*a1).v, 0x100*0x100 * 0x100);
	BOOST_CHECK_EQUAL((a2*a2).v, 0x7ff*0x7ff * 0x100);

	BOOST_CHECK_EQUAL((int)a0, 0x80);
	BOOST_CHECK_EQUAL((int)a1, 0x100);
	BOOST_CHECK_EQUAL((int)a2, 0x7ff);
}

BOOST_AUTO_TEST_CASE(fixed_point_rounding)
{
	gamma::fixed_point<24,8> a0(0x200,8), a1(0x199,8), a2(0x201,8), b0(0x180,8), b1(0x17f,8), b2(0x181,8);

	BOOST_REQUIRE(a0.v == 0x200);
	BOOST_REQUIRE(a1.v == 0x199);
	BOOST_REQUIRE(a2.v == 0x201);

	BOOST_REQUIRE(b0.v == 0x180);
	BOOST_REQUIRE(b1.v == 0x17f);
	BOOST_REQUIRE(b2.v == 0x181);

	BOOST_CHECK_EQUAL(a0.floor().v, 0x200); BOOST_CHECK_EQUAL(a1.floor().v, 0x100);	BOOST_CHECK_EQUAL(a2.floor().v, 0x200);
	BOOST_CHECK_EQUAL(b0.floor().v, 0x100); BOOST_CHECK_EQUAL(b1.floor().v, 0x100);	BOOST_CHECK_EQUAL(b2.floor().v, 0x100);

	BOOST_CHECK_EQUAL(a0.round().v, 0x200); BOOST_CHECK_EQUAL(a1.round().v, 0x200);	BOOST_CHECK_EQUAL(a2.round().v, 0x200);
	BOOST_CHECK_EQUAL(b0.round().v, 0x200); BOOST_CHECK_EQUAL(b1.round().v, 0x100);	BOOST_CHECK_EQUAL(b2.round().v, 0x200);

	BOOST_CHECK_EQUAL(a0.ceil().v, 0x200); BOOST_CHECK_EQUAL(a1.ceil().v, 0x200);	BOOST_CHECK_EQUAL(a2.ceil().v, 0x300);
	BOOST_CHECK_EQUAL(b0.ceil().v, 0x200); BOOST_CHECK_EQUAL(b1.ceil().v, 0x200);	BOOST_CHECK_EQUAL(b2.ceil().v, 0x200);
}