/* Copyright (c) 2013 Fabian Schuiki */
#include <gamma/vector.hpp>
#include <gamma/matrix.hpp>
#include <iostream>

using namespace gamma::convenience;

#define check(type, target) {\
	std::cout << #type " = " << sizeof(type);\
	if (sizeof(type) == target)\
		std::cout << " passed\n";\
	else {\
		std::cout << " failed, should be " << target << '\n';\
		failed++;\
	}\
}

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

int main()
{
	int failed = 0;

	check_vector(2);
	check_vector(3);
	check_vector(4);

	check_matrix(2);
	check_matrix(3);
	check_matrix(4);

	return failed;
}