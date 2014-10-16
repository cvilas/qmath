//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : VectorBase.hpp
// Description          : Template virtual base class for vectors
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
 
#ifndef INCLUDED_VectorBase_hpp
#define INCLUDED_VectorBase_hpp

#include <iostream>
#include <math.h>
#include "MatrixInitializer.hpp"

//====================================================================
// class VectorBase
// -------------------------------------------------------------------
// \brief
// The pure virtual base class for \c ColumnVector, \c RowVector and 
// \c Vector classes.
//========================================================================  
 
template<class T> class MatrixBase;

template<class T = double>
class VectorBase
{
 public:
  VectorBase(){}
   // The default constructor.
  
  virtual ~VectorBase(){}
   // The default destructor.

  virtual T *getElementsPointer() const = 0;
   //  return  A pointer to the first element in a vector.

  virtual T getElement(int i) const = 0;
   //  return  The element at the index i.

  virtual void setElement(int index, T value)= 0;
   // Sets an element to a value at the specified position.
   //  index  Position of the desired element.
   //  value  The desired element is set to this value.
	
  virtual int getNumElements() const  = 0;
   //  return  The number of elements in the vector.

  inline T norm() const;
   //  return 2-norm of the vector.
	
  virtual bool isRowVector() const = 0;
   //  return  'true' if the vector instantiated is a \c RowVector.

  bool isColumnVector() const {return !isRowVector(); }
   //  return  'true' if the vector instantiated is a \c ColumnVector.

  virtual MatrixInitializer<T> operator=(const T &value) = 0;
   // Initialize a vector object.
	
  void output(std::ostream &outputStream = std::cout);
   //  return  The elements in the vector to the output stream 
   //          (by default the output is to the console)

 protected:
  VectorBase(VectorBase<T> &m) {};
   // Copy constructor

   // ========== END OF INTERFACE ==========	
	
 private:
};


//=================================================================
// End of declarations.
//=================================================================

//======================================================================== 
// VectorBase::norm
//========================================================================  
template<class T>
T VectorBase<T>::norm() const
{
 T norm2 = 0;
 int size = getNumElements();
 for (int i = 1; i <= size; ++i)
 {
  norm2 += (T)(pow(getElement(i), 2.0));
 }
 return (T)sqrt(norm2);
}


//=======================================================================
// VectorBase::output
//=======================================================================
template<class T>
void VectorBase<T>::output(std::ostream &outputStream)
{
 int numElements = getNumElements();
 bool isRow = isRowVector();
	
 for (int i = 1; i <= numElements; ++i)
 {
  outputStream << getElement(i);
  if (isRow) outputStream << " ";
  else if(i < numElements) outputStream << "\n";
 }
}


#endif // INCLUDED_VectorBase_hpp

