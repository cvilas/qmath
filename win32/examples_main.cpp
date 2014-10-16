//======================================================================== 
// Package		: The Math Library - Ex
// Authors		: Vilas Kumar Chitrakaran
// Start Date	: Sun Oct 2 11:08:28 GMT 2005
// Compiler		: GNU C++ 2.95.3 and above
// ----------------------------------------------------------------------  
// File: examples_main.cpp
// Test programs for QMath in MSVC++
//========================================================================  

#include <stdio.h>
#include "examples_main.hpp"
#ifdef _MSC_VER
 #include <conio.h>
#endif


int main(int argc, char **argv)
{
	int ntests = 0;
	int npass = 0;

	if( test_Matrix(argc, argv) != 0 ) {
		fprintf(stderr, "Matrix: failed\n\n");
	} else {
		++npass;
		fprintf(stderr, "Matrix: passed\n\n");
	}
	++ntests;

	if( test_MathException(argc, argv) != 0 ) {
		fprintf(stderr, "MathException: failed\n\n");
	} else {
		++npass;
		fprintf(stderr, "MathException: passed\n\n");
	}
	++ntests;

	if( test_Vector(argc, argv) != 0 ) {
		fprintf(stderr, "Vector: failed\n\n");
	} else {
		++npass;
		fprintf(stderr, "Vector: passed\n\n");
	}
	++ntests;

	if( test_Transform(argc, argv) != 0 ) {
		fprintf(stderr, "Transform: failed\n\n");
	} else {
		++npass;
		fprintf(stderr, "Transform: passed\n\n");
	}
	++ntests;

	if( test_Adams3Integrator(argc, argv) != 0 ) {
		fprintf(stderr, "Adams3Integrator: failed\n\n");
	} else {
		++npass;
		fprintf(stderr, "Adams3Integrator: passed\n\n");
	}
	++ntests;

	if( test_Differentiator(argc, argv) != 0 ) {
		fprintf(stderr, "Differentiator: failed\n\n");
	} else {
		++npass;
		fprintf(stderr, "Differentiator: passed\n\n");
	}
	++ntests;

	if( test_Differentiator4O(argc, argv) != 0 ) {
		fprintf(stderr, "Differentiator4O: failed\n\n");
	} else {
		++npass;
		fprintf(stderr, "Differentiator4O: passed\n\n");
	}
	++ntests;

	if( test_HighpassFilter(argc, argv) != 0 ) {
		fprintf(stderr, "HighpassFilter: failed\n\n");
	} else {
		++npass;
		fprintf(stderr, "HighpassFilter: passed\n\n");
	}
	++ntests;

	if( test_Integrator(argc, argv) != 0 ) {
		fprintf(stderr, "Integrator: failed\n\n");
	} else {
		++npass;
		fprintf(stderr, "Integrator: passed\n\n");
	}
	++ntests;

	if( test_LowpassFilter(argc, argv) != 0 ) {
		fprintf(stderr, "LowpassFilter: failed\n\n");
	} else {
		++npass;
		fprintf(stderr, "LowpassFilter: passed\n\n");
	}
	++ntests;

	if( test_ODESolverRK4(argc, argv) != 0 ) {
		fprintf(stderr, "ODESolverRK4: failed\n\n");
	} else {
		++npass;
		fprintf(stderr, "ODESolverRK4: passed\n\n");
	}
	++ntests;

	if( npass == ntests) {
		fprintf(stderr, "ALL TESTS PASSED\n\n");
	} else{
		fprintf(stderr, "ONLY %d/%d OF ALL TESTS PASSED\n\n", npass, ntests);
	}

#ifdef _MSC_VER
	_getch();
#endif

	return 0;
}