//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : MatrixInitializer.hpp
// Description          : Template class for handle initialization of 
//                        matrices and vectors
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
 

#ifndef INCLUDED_MatrixInitializer_hpp
#define INCLUDED_MatrixInitializer_hpp

#include "MathException.hpp"

//======================================================================== 
// class MatrixInitializer
// ----------------------------------------------------------------------
// \brief
// This class is used internally by the library to initialize the \c Matrix 
// and its derived class objects.
//
//========================================================================  

template<int numRows, int numColumns, class T> class Matrix;

template<class T = double>
class MatrixInitializer
{
 public:
  inline MatrixInitializer (T num, int offset, T *firstElementPointer);
   // The default constructor.

  ~MatrixInitializer (){}
   // The default destructor.

  inline MatrixInitializer<T>  operator,(const T &elementValue);
   // This function provides a method to
   // easily assign the elements of a Matrix 
   // object. A Matrix object is initialized in
   // the following manner:
   // \code Matrix<2,2> myMatrix;
   // myMatrix = 2.0, 5.0, 78.90, 20; \endcode
   
 // ========== END OF INTERFACE ==========
 
 private:
  T d_numElements;
  int d_positionCounter;
  T *d_firstElementPointer; 
};


//========================================================================
// MatrixInitializer::MatrixInitializer 
//========================================================================
template<class T>
MatrixInitializer<T>::MatrixInitializer (T totalElements, int offset, T *firstElementPointer)
{	
 d_numElements = totalElements;
 d_firstElementPointer = firstElementPointer;
 d_positionCounter = offset;
}


//========================================================================
// MatrixInitializer::operator, 
//========================================================================
template<class T>
MatrixInitializer<T>  MatrixInitializer<T>::operator,(const T &elementValue)
{
 if (d_positionCounter > (d_numElements-1))
 { 
  static MathException exception;
  exception.setErrorType(QMathException_illegalIndex);
  throw exception;
 }

 *(d_firstElementPointer + d_positionCounter) = elementValue;
 ++d_positionCounter;
 MatrixInitializer<T>  matrixInitialize(d_numElements,d_positionCounter, d_firstElementPointer);
 return matrixInitialize;
}

#endif
