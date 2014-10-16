//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : Transform.t.cpp
// Description          : Example program for the Transform class.
//========================================================================

//========================================================================
// Transform.t.cpp
//------------------------------------------------------------------------
// This program demonstrates how to find the values of the
// components of a vector in a fixed reference frame after the 
// vector undergoes a series of transformations about the frame.
//========================================================================

#include "Transform.hpp"
#include <math.h>
#ifndef M_PI
 #define M_PI 3.14159265358979323846
#endif

using namespace std;

// If using GNUC makefile, just compile main function here. If using 
// MS Visual C++, the main function is in examples_main.cpp
#if defined(__GNUC__)
    #define test_Transform(argc, argv) main(argc, argv)
#endif

int test_Transform(int argc, char **argv)

{
 ColumnVector<4, double> initialVector;
 ColumnVector<4, double> finalVector;
 Transform firstRotation;
 Transform secondRotation;
 Transform transform;

 // The initial position is [1 0 0 1] in homogeneous coordinates
 initialVector = 1, 0, 0, 1;
	
 // Finding the new co-ordinates. (Angles must be specified in radians.)
 transform = xRotation(0.5 * M_PI) * yRotation(0.5 * M_PI)  * translation(0,0,6);

 finalVector = transform * initialVector;
 cout << "* Position vector after transformation in fixed frame : " 
      << transpose(finalVector) << endl;
 cout << "* Translation : " << transpose(transform.getTranslation()) << endl;

 // To get the roll/pitch/yaw angles of the new vector.
 double roll;
 double pitch;
 double yaw;
	
 transform.getRollPitchYaw(roll, pitch, yaw);
 roll *= 180.0/M_PI; pitch *= 180.0/M_PI; yaw *= 180.0/M_PI;
 cout << "* (yaw, pitch, roll) angles of the new vector (degrees) : (" 
      << yaw << "," << pitch << "," << roll << ")" << endl;
	
 // You can get back the initial position vector by the inverse transformation..
 ColumnVector<4, double> initialVectorAgain;
 initialVectorAgain = inverse(transform) * finalVector;

 cout << "* After inverse transform : " << transpose(initialVectorAgain) << endl;
 cout << "* Should be the same as what we began with : " << transpose(initialVector) << endl;

 return 0;
}
