/* Copyright (c) 2013 Fabian Schuiki */
#include <gamma/matrix.hpp>
#include <iostream>

using namespace gamma::convenience;

#define verify_column_major(type, dim) {\
	std::cout << "verify " #type " column-major";\
	type m;\
	m.m10 = 1;\
	m.m01 = 2;\
	if (m.a[0][1] != 1 || m.a[1][0] != 2) {\
		std::cout << " failed\n";\
		failed++;\
	} else\
		std::cout << " passed\n";\
}

#define verify_column_major_matrices(dim)\
	verify_column_major(matrix ## dim ## b, dim);\
	verify_column_major(matrix ## dim ## i, dim);\
	verify_column_major(matrix ## dim ## f, dim);\
	verify_column_major(matrix ## dim ## d, dim);

int main()
{
	int failed = 0;
	verify_column_major_matrices(2);
	verify_column_major_matrices(3);
	verify_column_major_matrices(4);
	return failed;
}