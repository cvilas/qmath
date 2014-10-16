//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : MatrixBase.hpp
// Description          : Template virtual base class for matrices
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

#ifndef INCLUDED_MatrixBase_hpp
#define INCLUDED_MatrixBase_hpp 

#include <iostream>
#include "MatrixInitializer.hpp"

//====================================================================
// class MatrixBase
// -------------------------------------------------------------------
// \brief
// This is a pure virtual base class for \c Matrix.
//====================================================================

template<class T = double>
class MatrixBase
{
 public:
  MatrixBase() {}
   // The default constructor.

  virtual ~MatrixBase() {}
   // The default destructor.

  virtual T *getElementsPointer() const = 0;
   //  return  The pointer to the first element in a matrix or vector.
		
  virtual int getNumElements() const {return getNumColumns() * getNumRows();};
   //  return  The number of elements in the Matrix.

  virtual int getNumRows() const = 0;
   //  return  The number of rows in the Matrix.

  virtual int getNumColumns() const = 0;
   //  return  The number of columns in the Matrix.

  virtual T getElement(int row, int column) const = 0;
   //  return  The element at the specified position.

  virtual void setElement(int row, int column, T value)= 0;
   // Sets an element to a value at the specified position.
   //  row	Row number of the desired element.
   //  column	Column number of the desired element.
   //  value	The desired element is set to this value.

  virtual MatrixInitializer<T> operator=(const T &value) = 0;
   // Initialization of matrix.
   //  value  The value to which all elements in the matrix
   //         are initialized.
	
  void output(std::ostream &outputStream = std::cout);
   //  return  The elements in the referenced matrix to 
   //          the output stream (by default the
   //          output is to the console)
		
 protected:
  MatrixBase(const MatrixBase<T> &m) {m;/*removes compiler warning*/};
   // Copy Constructor.

  // ========== END OF INTERFACE ==========
};


//=======================================================================
// MatrixBase::output
//=======================================================================
template<class T>
void MatrixBase<T>::output(std::ostream &outputStream)
{
 int numRows = getNumRows();
 int numColumns = getNumColumns();
	
 for (int r = 1; r <= numRows; ++r)
 {
  for (int c = 1; c <= numColumns; ++c)
  {
   outputStream << getElement(r, c) << " ";
  }
  if (r < numRows) outputStream << "\n";
 }
}


#endif
