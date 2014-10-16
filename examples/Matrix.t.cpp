//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : Matrix.t.cpp
// Description          : Example program for the class Matrix.
//========================================================================

#include "Matrix.hpp"
#include "ColumnVector.hpp"
#include "RowVector.hpp" 

using namespace std;

//========================================================================
// This example demonstrates solving the foll. simultaneous eqns
// 2 * x1 + 8 * x2 + 5 * x3 = 5,
// 1 * x1 + 1 * x2 + 1 * x3 = -2,
// 1 * x1 + 2 * x2 - 1 * x3 = 2.
//========================================================================
// If using GNUC makefile, just compile main function here. If using 
// MS Visual C++, the main function is in examples_main.cpp
#if defined(__GNUC__)
    #define test_Matrix(argc, argv) main(argc, argv)
#endif

int test_Matrix(int argc, char **argv)

{
 Matrix<3,3> A;
 Matrix<2,3> A1;
 ColumnVector<3> x;
 ColumnVector<3> b;

 // Write in Ax = b form
 A = 2, 8, 5,
     1, 1, 1, 
     1, 2, -1;

 b = 5, -2, 2;
 
 // solve for x
 x = inverse(A) * b;
 cout << "solution: " << transpose(x) << endl;

 return 0;
}
