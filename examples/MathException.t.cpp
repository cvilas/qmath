//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : MathException.t.cpp
// Description          : Example program for the class MathExceptions.
//========================================================================  
 
#include "Matrix.hpp"

using namespace std;

// If using GNUC makefile, just compile main function here. If using 
// MS Visual C++, the main function is in examples_main.cpp
#if defined(__GNUC__)
    #define test_MathException(argc, argv) main(argc, argv)
#endif

int test_MathException(int argc, char **argv)
{

 Matrix<2,2> m1, m2;

 m1 = 1.0, 5.6, 2.7, 8.4;
 
 // Enclose critical code inside try block.
 //subsequent catch block catches exceptions
 try
 {
  m2 = m1/0.0; /* divide by zero! */
 }
 catch (MathException &ex)
 {
  cout << ex.getErrorMessage() << endl;
  /* do exception recovery here */
  return 0;
 }
 cout << "This line won't print" << endl;
 return 0;
}
