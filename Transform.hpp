//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : Transform.hpp
// Description          : Template class for homogeneous transformations
//
// Copyright (C) 2000 Vilas Chitrakaran
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published 
// by the Free Software Foundation; either version 2 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//========================================================================  
 
#ifndef INCLUDED_Transform_hpp
#define INCLUDED_Transform_hpp

#ifdef QMATH_DLL
 #ifdef QMATH_DLL_EXPORT
  #define QMATHDLL_API __declspec(dllexport)
 #else
  #define QMATHDLL_API __declspec(dllimport)
 #endif
#else
 #define QMATHDLL_API
#endif

#include <float.h>
#include "Matrix.hpp"
#include "ColumnVector.hpp"
#include "RowVector.hpp"

#ifdef _MSC_VER
 #define finite(n) _finite(n)
#endif


//====================================================================
// class Transform
// -------------------------------------------------------------------
// \brief
// The class \c Transform represents a 4x4 homogeneous transformation 
// matrix.
//
// <b>Example Program:</b>
// \include Transform.t.cpp
//========================================================================  
 
class QMATHDLL_API Transform : public Matrix <4, 4, double>
{
 public:
  inline Transform();
   // The default constructor for the
   // \c Transform object. The \c Transform
   // matrix is initialized to the following form.
   // \code
   //	[1 0 0 0]
   //	[0 1 0 0]
   //	[0 0 1 0]
   //	[0 0 0 1]
   // \endcode

  inline Transform(const Transform &transform);
   // Copy Constructor.

  ~Transform() {}
   // The default destructor.
	
  inline MatrixInitializer<double> operator=(const double &val);
   // This function provides an overloaded assignment
   // operator for initializing the elements of a Transform.
   // The initialization of the Transform object can be 
   // done as a comma seperated list. For example:
   // \code Transform myTransform;
   // myTransform = cos(x), sin(x),...so on ; \endcode
   //  val  The comma separated list of elements.
		
  inline ColumnVector<3,double> getTranslation() const;
   //  return  The position vector (last column) from the matrix.
		
  inline void getRollPitchYaw(double &roll, double &pitch, double &yaw) const;
   // This function returns the roll (z), pitch (y) and yaw (x) angles from the
   // homogeneous transformation matrix. The angles are defined as follows: 
   // The rotational part of the Transform matrix is obtained by 
   // first defining a rotation about X axis by \c yaw radians, 
   // then a rotation about the Y axis by \c pitch radians and 
   // finally a rotation about the Z axis by \c roll radians, 
   // all rotations being relative to a fixed XYZ frame. The definition follows
   // the description in the following textbook:
   // M. W. Spong, and M. Vidyasagar, Robot Dynamics and Control, John 
   // Wiley and Sons, ISBN: 047161243, 1989.
   // <hr>NOTE: There are multiple solutions (combinations of angles) that
   // result in the same rotation matrix, but are physically different 
   // orientations. This function returns a solution corresponding to 
   // cos(pitch) > 0, i.e., -pi/2 < pitch < pi/2. If the assumption that 
   // cos(pitch) > 0 does not hold, incorrect solutions are returned. Beware of
   // gimbal lock that happens when cos(pitch) = 0, in which case, the roll and 
   // the yaw angles are indistinguishable.<hr> 
   //  roll, pitch, yaw  The angles extracted from the transformation matrix.
		
 private:
};

inline QMATHDLL_API Transform operator* (const Transform &firstTransfrom, const Transform &secondTransform);
 // Overloading binary operator * for multiplication between two transforms.

inline Transform inverse(const Transform &t);
 //  return  The inverse of the transform \a t.

inline QMATHDLL_API Transform translation(double x, double y, double z);
 //  return  A \a Transform representing a translation of \a x, \a y and \a z 
 //          units in the X, Y and Z directions.

QMATHDLL_API Transform xRotation(double theta);
 //  return  A \a Transform representing a rotation of angle 
 //          \a theta radians about the X axis.

QMATHDLL_API Transform yRotation(double theta);
 //  return  A \a Transform representing a rotation 
 //          of angle \a theta about the Y axis.

QMATHDLL_API Transform zRotation(double theta);
 //  return  A \a Transform representing a rotation of angle 
 //          \a theta radians about the Z axis.

QMATHDLL_API Transform vectorRotation(const ColumnVector<3, double> &vector, double theta);
 //  return  A \a Transform representing a rotation of angle \a theta 
 //          radians about an arbitrary vector \a vector (computed using
 //          Rodrigues formula.

inline QMATHDLL_API Transform rpyRotation(double roll, double pitch, double yaw);
 // Sets the rotational part of the transform matrix from the 
 // \c roll, \c pitch and \c yaw angles as described in the following: 
 // M. W. Spong, and M. Vidyasagar, Robot Dynamics and Control, John Wiley and 
 // Sons, ISBN: 047161243, 1989. The rotational part
 // of the Transform matrix is obtained by first defining 
 // a rotation about X axis by \c yaw radians, then a rotation 
 // about the Y axis by \c pitch radians and finally a rotation 
 // about the Z axis by \c roll radians, all rotations being 
 // relative to a fixed XYZ frame.
 //  yaw	Rotation about the X axis.
 //  pitch	Successive rotation about the Y axis.
 //  roll	Successive rotation about the Z axis.
 //  return     A transformation matrix with the rotation matrix set.

// ========== END OF INTERFACE ==========


//============================================================= 
// Transform::Transform: Constructor of the Transform class
//=============================================================  
Transform::Transform() : Matrix<4,4,double>()
{
 for(int i = 0; i < 16; ++i)
  d_element[i] = 0;
 d_element[0] = 1;
 d_element[5] = 1;
 d_element[10] = 1;
 d_element[15] = 1;
}


Transform::Transform(const Transform &t):Matrix<4,4,double>(t)
{
}


//============================================================= 
// Transform::operator=
//=============================================================  
MatrixInitializer<double> Transform::operator=(const double &elementValue)
{
 return this->Matrix<4, 4, double>::operator=(elementValue);
}


//============================================================= 
// Transform::getTranslation
//=============================================================  
ColumnVector<3,double> Transform::getTranslation() const
{
 ColumnVector<3, double> translation;	 
 for (int i = 0; i < 3; ++i)
  translation(i+1) = d_element[i * 4 + 3];
 return translation;
}


//============================================================= 
// Transform::getRollPitchYaw
//=============================================================  
void Transform::getRollPitchYaw(double &roll, double &pitch, double &yaw) const
{
 double cp;
 pitch = -asin(d_element[8]); //[2][0]
 cp = cos(pitch);
 if( finite(1.0/cp) ) {
  yaw = atan2(d_element[9]/cp, d_element[10]/cp); // R32/R33
  roll = atan2(d_element[4]/cp, d_element[0]/cp); // R21/R11
 } else { // gimbal lock
  roll = 0;
  yaw = atan2(d_element[1], d_element[2]); // R12/R13
 }
}


//============================================================= 
// operator*
//=============================================================  
Transform operator* (const Transform &t1, const Transform &t2)
{
 Transform p;
 for (int r = 1; r <= 4; ++r)
 {
  for (int c = 1; c <= 4; ++c)
  {
   double s = 0;
   for (int cd = 1; cd <= 4; ++cd)
    s += t1.getElement(r, cd) * t2.getElement(cd, c);
   p(r, c) = s;
  }
 }
 return p;
}


//============================================================= 
// inverse
//=============================================================  
Transform inverse(const Transform &transform)
{
 Transform invertedTransform;

 Matrix<3,3,double> rotation;
 ColumnVector<3, double> position;

 position = transform.getTranslation();
 transform.getSubMatrix(1,1,rotation);
 invertedTransform.setSubMatrix(1,1,(transpose(rotation)));
 invertedTransform(1,4) = -dotProduct(position, rotation.getColumn(1));
 invertedTransform(2,4) = -dotProduct(position, rotation.getColumn(2));
 invertedTransform(3,4) = -dotProduct(position, rotation.getColumn(3));

 return invertedTransform;
}


//============================================================= 
// translation
//=============================================================  
Transform translation(double x, double y, double z)
{
 Transform translation;
 for (int row = 1; row <= 4; ++row)
 {
  for (int column = 1; column <= 4; ++column)
  { 
   (row==column)?(translation(row,column)=1):(translation(row,column)=0);
  }
 }
 translation(1,4) = x;
 translation(2,4) = y;
 translation(3,4) = z;
 return translation;
}


//============================================================= 
// rpyRotation
//=============================================================  
Transform rpyRotation(double roll, double pitch, double yaw)
{
 Transform rpyRotation;
 rpyRotation = (zRotation(roll) * yRotation(pitch)) * xRotation(yaw);
 return rpyRotation;
}


#endif

