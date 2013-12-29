/* Copyright (c) 2013 Fabian Schuiki */
#define BOOST_TEST_MODULE gamma
#include <gamma/integer.hpp>
#include <gamma/vector.hpp>
#include <gamma/matrix.hpp>
#include <gamma/fixed_point.hpp>
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
	gamma::fixed_point<int, 8> fp0, fp1;
	fp0.v = 0x00008000;
	fp1.v = 0x00010000;

	BOOST_CHECK_EQUAL((int)(fp0*fp0), 0x80*0x80);
	BOOST_CHECK_EQUAL((int)(fp1*fp1), 0x100*0x100);
}