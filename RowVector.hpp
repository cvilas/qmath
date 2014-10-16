//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : RowVector.hpp
// Description          : Template class for row vectors
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

#ifndef INCLUDED_RowVector_hpp
#define INCLUDED_RowVector_hpp

#include "VectorBase.hpp"
#include "Matrix.hpp"

//====================================================================
// class RowVector
// -------------------------------------------------------------------
// \brief
// A class for row vectors.
//
// The class \c RowVector is derived from the base classes \c Matrix
// and \c VectorBase, and provides methods for operations such as 
// cross product, dot product and element-by-element multiplication.
//
// <b>Example Program: </b>See the example of the class \c ColumnVector.
//========================================================================  
 
template<int size, class T = double>
class RowVector : public Matrix <1, size, T>, public VectorBase<T>
{
 public:
  inline RowVector()  : Matrix<1,size,T>(), VectorBase<T>(){}
   // The default constructor. The elements are not initialized.
	
  inline RowVector(const RowVector<size, T> &rowVector);
   // Copy Constructor. 

  inline RowVector(const Matrix<1, size, T> &matrix);
   // The conversion constructor for conversion
   // of a \c Matrix type of single row into
   // type \c RowVector.

  ~RowVector(){}
   // The default destructor

  virtual T *getElementsPointer() const { return (T *)(this->d_element); }
   //  return A pointer to the first element in the vector.

  inline virtual T getElement(int index) const;
   //  return  The value at position specified by index 
   //          (index = 1 is the first element).

  inline virtual void setElement(int index, T value);
   // Sets an element to a value at the specified position.
   //  index  Position of the desired element.
   //  value  The desired element is set to this value.

  virtual bool isRowVector() const {return true;}
   //  return  true

  virtual int getNumElements() const {return size;}
   //  return The number of elements in the vector.

  inline T operator()(int index) const;
  inline T &operator()(int index);
   // Access or assign the element at the position specified by 
   // index. For example: 
   // \code 
   // myVector(2)=12.65; 
   // \endcode
	
  inline RowVector<size, T> &operator=(const RowVector<size, T> &v);
   // Assignment between two \c RowVector types of same dimensions.

  MatrixInitializer<T> operator=(const T &value);
   // Initialize a vector object.
   //  value  The value to which all elements in the vector are initialized.
   // The initialization of the vector object can also
   // be done as a comma seperated list. For example:
   // \code 
   // ColumnVector<3> myVector;
   // myVector = 67.88, 45.89, 90; 
   // \endcode
 private:
};


template<class T>
RowVector<3,T> crossProduct(const RowVector<3, T> &v1, const RowVector<3, T> &v2);
 // Generates the cross product of two 3 dimensional row vectors. 
 //  v1, v2  The 3D row vector arguments.
 //  return  The cross product.

template<int size, class T>
RowVector<size, T> elementProduct(const RowVector<size, T> &v1, const RowVector<size, T> &v2);
 // This function performs multiplication between two column vectors element-by-element.
 //  v1, v2  The row vector arguments
 //  return  The product.


template<int size, class T>
T dotProduct(const RowVector<size,T> &v1, const RowVector<size, T> &v2);
 // Dot (inner) product between two row vectors.
 //  v1, v2 The row vector arguments.
 //  return  The scalar product.

template<int size, class T>
ColumnVector<size, T> transpose(const RowVector<size, T> &vector);
  // return  The transpose of the type \c ColumnVector.

// ========== END OF INTERFACE ==========



//======================================================================== 
// RowVector::RowVector: Constructor of the RowVector class
//========================================================================  
template<int size, class T>
RowVector<size, T>::RowVector(const Matrix<1, size, T> &matrix)
 : Matrix<1,size,T>(matrix), VectorBase<T>()
{
}

template<int size, class T>
RowVector<size, T>::RowVector(const RowVector<size, T> &r)
 : Matrix<1,size,T>(r), VectorBase<T>()
{
}


//======================================================================== 
// RowVector::getElement
//========================================================================  
template<int size, class T>
T RowVector<size, T>::getElement(int i) const
{
 if( i > size || i < 1)
 {
  static MathException exception;
  exception.setErrorType(QMathException_illegalIndex);
  throw exception;
 }
 return this->d_element[(i-1)];
}


//======================================================================== 
// RowVector::setElement
//========================================================================  
template<int size, class T>
void RowVector<size, T>::setElement(int i, T value)
// Sets an element to a value at the specified position.
{
 if( i > size || i < 1)
 {
  static MathException exception;
  exception.setErrorType(QMathException_illegalIndex);
  throw exception;
 }
 this->d_element[(i-1)] = value;
}


//======================================================================== 
// RowVector::operator()
//========================================================================  
template<int size, class T>
T RowVector<size, T>::operator()(int i) const
{
 if( i > size || i < 1)
 {
  static MathException exception;
  exception.setErrorType(QMathException_illegalIndex);
  throw exception;
 }
 return this->d_element[(i-1)];
}

template<int size, class T>
T &RowVector<size, T>::operator()(int i)
{
 if( i > size || i < 1)
 {
  static MathException exception;
  exception.setErrorType(QMathException_illegalIndex);
  throw exception;
 }
 return this->d_element[(i-1)];
}


//======================================================================== 
// RowVector::operator=
//========================================================================  
template<int size, class T>
RowVector<size, T> &RowVector<size, T>::operator=(const RowVector<size, T> &v)
{
 if( this == &v )
  return *this;

 for(int i = 0; i < size; ++i)
  this->d_element[i] = v.d_element[i];
 return *this;
}

template<int size, class T>
MatrixInitializer<T> RowVector<size, T>::operator=(const T &value)
{
 for (int i = 0; i < size; ++i)
 {
  this->d_element[i] = value;
 }
 MatrixInitializer<T>  matrixInitialize(size, 1, this->d_element);
 return matrixInitialize;
}


//======================================================================== 
// crossProduct
//========================================================================  
template<class T>
RowVector<3,T> crossProduct(const RowVector<3, T> &v1, const RowVector<3, T> &v2)
{
 RowVector<3, T> cp;
 cp(1) = v1(2)*v2(3) - v1(3)*v2(2);
 cp(2) = v1(3)*v2(1) - v1(1)*v2(3);
 cp(3) = v1(1)*v2(2) - v1(2)*v2(1);
 return (cp);
}


//======================================================================== 
// elementProduct
//========================================================================  
template<int size, class T>
RowVector<size, T> elementProduct(const RowVector<size, T> &v1, const RowVector<size, T> &v2)
{
 RowVector<size, T> ep;
 for (int i = 1; i <= size; ++i)
  ep(i) = v1(i)*v2(i);
 return (ep);
}


//======================================================================== 
// dotProduct
//========================================================================  
template<int size, class T>
T dotProduct(const RowVector<size, T> &v1, const RowVector<size, T> &v2)
{
 T dp = 0;
 for (int i = 1; i <= size; ++i)
  dp += v1(i) * v2(i);
 return (dp);
}


//======================================================================== 
// transpose
//========================================================================  
template<int size, class T>
ColumnVector<size, T> transpose(const RowVector<size, T> &vector)
{
 ColumnVector<size,T> column;
 for (int i = 1; i <= size; ++i)
  column(i) = vector(i);
 return column;
}


#endif

