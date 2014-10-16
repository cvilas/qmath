//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : Vector.t.cpp
// Description          : Example program for the vector classes.
//========================================================================

#include "Vector.hpp"
#include "RowVector.hpp"

using namespace std;

// If using GNUC makefile, just compile main function here. If using 
// MS Visual C++, the main function is in examples_main.cpp
#if defined(__GNUC__)
    #define test_Vector(argc, argv) main(argc, argv)
#endif

int test_Vector(int argc, char **argv)
{
 Vector<3> v1, v2, v3;
 
 v1 = 1, 1, 2;
 v2 = 2, 3, 4;
 double dp;
  
 // dot product: component of v1 along v2
 dp = dotProduct(v1, v2);
 cout << "Dot product: v1 . v2 = " << dp << endl;
 
 // cross product: v1 x v2
 v3 = crossProduct(v1, v2);
 cout << "Cross product: v1 x v2 = " << transpose(v3) << endl; 

 // 2-norm of a vector
 cout << "norm(v1): " << v1.norm() << endl;
 return 0;
}

