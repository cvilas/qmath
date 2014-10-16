//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : Transform.cpp
// Description          : Implementation of Transform class
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
 
// ----- Project Includes -----
#include "Transform.hpp"

//============================================================= 
// xRotation
//=============================================================  
Transform xRotation(double theta)
{
 Transform xRotation;
 xRotation(1,1) = 1;
 xRotation(2,2) = cos(theta);
 xRotation(2,3) = -sin(theta);
 xRotation(3,2) = -xRotation(2,3);
 xRotation(3,3) = xRotation(2,2);
 return xRotation;
}


//============================================================= 
// yRotation
//=============================================================  
Transform yRotation(double theta)
{
 Transform yRotation;
 yRotation(1,1) = cos(theta);
 yRotation(1,3) = sin(theta);
 yRotation(2,2) = 1;
 yRotation(3,1) = -yRotation(1,3);
 yRotation(3,3) = yRotation(1,1);
 return yRotation;
}


//============================================================= 
// zRotation
//=============================================================  
Transform zRotation(double theta)
{
 Transform zRotation;
 zRotation(1,1) = cos(theta);
 zRotation(1,2) = -sin(theta);
 zRotation(2,1) = -zRotation(1,2);
 zRotation(2,2) = zRotation(1,1);
 zRotation(3,3) = 1;
 return zRotation;
}


//============================================================= 
// vectorRotation
//=============================================================  
Transform vectorRotation(const ColumnVector<3, double> &u, double theta)
{
 Transform t;
 double c = cos(theta);
 double s = sin(theta);
 Matrix<3, 3, double> r;
 r(1,1) = 0;
 r(1,2) = -u(3)*s;
 r(1,3) = u(2)*s;
 r(2,1) = -r(1,2);
 r(2,2) = r(1,1);
 r(2,3) = -u(1)*s;
 r(3,1) = -r(1,3);
 r(3,2) = -r(2,3);
 r(3,3) = r(1,1);
 r += u*transpose(u)*(1-c);
 r(1,1) += c;
 r(2,2) += c; 
 r(3,3) += c;
 t.setSubMatrix(1, 1, r);
 return t;
}


