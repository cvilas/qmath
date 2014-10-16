//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : Vector.hpp
// Description          : Alternative template class for column vectors
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
 
#ifndef INCLUDED_Vector_hpp
#define INCLUDED_Vector_hpp

#include "ColumnVector.hpp" 
 
//======================================================================== 
// class Vector
// ----------------------------------------------------------------------
// \brief
// The class \c Vector provides is equivalent to a \c ColumnVector object.
//
// <b>Example Program:</b> See the Example program for class ColumnVector.
//========================================================================  
 
template<int size, class T = double>
class Vector : public ColumnVector<size, T>
{
 public:
  inline Vector ()  : ColumnVector<size,T>() {}
   // The default constructor. No element initializations.

  inline Vector(const Vector<size, T> &vector);
   // Copy Constructor. 

  inline Vector(const Matrix<size,1,T> &matrix);
   // The conversion constructor for conversion
   // of a \c Matrix type of single column into
   // type \c Vector.

  ~Vector () {}
   // The default Destructor.
		
  MatrixInitializer<T> operator=(const T &value);
   // Initialize a vector object.
   //  value  The value to which all elements in the vector are initialized.
   // The initialization of the vector object can also
   // be done as a comma seperated list. For example:
   // \code 
   // ColumnVector<3> myVector;
   // myVector = 67.88, 45.89, 90; 
   // \endcode

  // ========== END OF INTERFACE ==========
 private:
};



//======================================================================== 
// Vector::Vector
//========================================================================  
template<int size, class T>
Vector<size, T>::Vector(const Vector<size, T> &v)
 : ColumnVector<size,T>(v)
{
}

template<int size, class T>
Vector<size, T>::Vector(const Matrix<size,1,T> &m)
 : ColumnVector<size,T>(m)
{
}


//======================================================================== 
// Vector::operator=
//========================================================================  
template<int size, class T>
MatrixInitializer<T>Vector<size, T>::operator=(const T &value)
{
 return this->ColumnVector<size, T>::operator=(value);
}


#endif

