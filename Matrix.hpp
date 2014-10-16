//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : Matrix.hpp
// Description          : Template class for matrices
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
 
#ifndef INCLUDED_Matrix_hpp
#define INCLUDED_Matrix_hpp

#include "MatrixBase.hpp" 
#include "VectorBase.hpp"
#include <iostream>
#include <iomanip>
#include <math.h>

template<int r, int c, class T> class Matrix;
template<int n, class T> class ColumnVector; 
template<int n, class T> class RowVector;
template<class T>class MatrixInitializer;
template<int r, int c, class T> Matrix<r,c,T> operator+(const Matrix<r, c, T> &lhs, const Matrix<r, c, T> &rhs);
template<int r, int c, class T> Matrix<r,c,T> operator-(const Matrix<r, c, T> &lhs, const Matrix<r, c, T> &rhs);
template<int r, int c, class T> Matrix<r,c,T> operator*(const Matrix<r, c, T> &lhs, const T &s);
template<int r, int c, class T> Matrix<r, c, T> operator*(const T &s, const Matrix<r, c, T> &rhs);
template<int r, int c, class T> Matrix<r,c,T> operator/(const Matrix<r, c, T> &lhs, const T &s);
template<int r, int c, class T> std::ostream &operator<< (std::ostream &out, const Matrix<r,c,T> &m);
template<int r, int c, class T> std::istream &operator>> (std::istream &in, Matrix<r,c,T> &m);
template<int r, int c, class T> bool operator==(const Matrix<r,c,T> &lhs, const Matrix<r,c,T> &rhs);
template<int r, int c, class T> bool operator!=(const Matrix<r,c,T> &lhs, const Matrix<r,c,T> &rhs);


//==============================================================================
// class Matrix
// -----------------------------------------------------------------------------
// \brief
// Methods for mathematical operations on matrices.
//
// The class \c Matrix is derived from its base class \c MatrixBase.
//
// This class provides common mathematical functions for matrices such 
// as addition, multipication and subtraction between matrices, 
// along with methods to get/set elements/sub-matrices. The template class 
// also provides methods for determination of the inverse of a matrix upto 
// 4 x 4, the transpose of a matrix and generation of unit matrices. 
// The classes \c ColumnVector, \c RowVector and \c Transform are 
// derived from this class.
//
// <b>Example Program:</b>
// \include Matrix.t.cpp
//============================================================================== 
template<int nRows, int nCols, class T = double>
class Matrix : public MatrixBase<T>
{
 public:
  inline Matrix() {d_size = nRows * nCols;};
   // The default constructor for the \c Matrix object.
   // The elements of Matrix are not initialized.
	
  inline Matrix(const Matrix<nRows, nCols, T> &matrix);
   // Copy Constructor.

  virtual ~Matrix() {}
   // The default destructor of the \c Matrix object.
	
  virtual T *getElementsPointer() const { return (T *) d_element; }
   //  return  The pointer to the first element in the Matrix.
		
  virtual int getNumRows() const {return nRows;}
   //  return  The number of rows in the Matrix.

  virtual int getNumColumns() const {return nCols;}
   //  return 	The number of columns in the Matrix.
	
  inline ColumnVector<nRows, T> getColumn(int c) const;
   //  return  The column specified by \a c.
   // Example: 
   // \code 
   // ColumnVector<3> c;
   // Matrix<3,3> m;
   // c = m.getColumn(1); // extract first column
   // \endcode
 
  inline RowVector<nCols, T> getRow(int r) const;
   //  return  The row specified by \a r.
   // Example: see getColumn()
   
  inline virtual T getElement(int r, int c) const;
   // returns the element at the specified position.
   //  r  Row number of the desired element.
   //  c  Column number of the desired element.

  inline virtual void setElement(int r, int c, T val);
   // Sets an element to a value at the specified position.
   //  r    Row number of the desired element.
   //  c    Column number of the desired element.
   //  val  The desired element is set to this value.

  template<int sr, int sc, class X>
  void getSubMatrix(int pivotRow, int pivotColumn, Matrix<sr, sc, X> &m) const; 
   // This function extracts a sub-matrix of the size of \a m (sr x sc) starting 
   // from the specified pivotal row and column (that defines the top left 
   // corner of sub matrix).
   //  pivotRow, pivotColumn  The position of the first element of the sub-matrix 
   //                         in the matrix from which it is extracted.
   //  m                      The extracted sub matrix.
   // Example: 
   // \code 
   // Matrix<2,2> s;
   // Matrix<4,4> m;
   // //extract s = [m(1,3), m(1,4); m(2,3), m(2,4)]
   // m.getSubMatrix(1,3,s); 
   // \endcode
																
  template<int sr, int sc, class X>
  void setSubMatrix(int pivotRow, int pivotColumn, const Matrix<sr, sc, X> &m);
   // This function sets a sub-matrix of the size of \a m (sr x sc) starting from 
   // the pivotal row and column within the matrix.
   //  pivotRow, pivotColumn  The position of the first element	of the sub-matrix 
   //                         in the matrix to  which it is extracted.
   //  m                      The sub-matrix.				
   // Example: 
   // \code 
   // Matrix<2,2> s;
   // Matrix<3,2> m;
   // //set m = [m(1,1), s(1,1), s(1,2); m(2,1), s(2,1), s(2,2)]
   // m.getSubMatrix(1,2,s); 
   // \endcode
	
  inline T operator()(int r, int c) const; 
  inline T &operator()(int r, int c); 
   // Access or assign the element at \a r row and \a c column of the matrix.
   // Example: \code myMatrix(2,3)=22.2; \endcode
			
  inline MatrixInitializer<T> operator=(const T &val);
   // Assignment operator for initializing a Matrix object.
   //  val  This is the value to which all elements in the matrix
   //       are initialized.
   // The initialization of the Matrix object can also
   // be done as a comma seperated list. For example:
   // \code Matrix<2,2> myMatrix;
   // myMatrix = 67.899, 23.45, 6, 98; \endcode

  inline Matrix<nRows, nCols, T> &operator=(const Matrix<nRows, nCols, T> &m);
   // Assign a \a MatrixBase type to a \a Matrix type. The dimensions 
   // of both the objects must be the same.
   //  m  The object of the base class \a MatrixBase.

  inline Matrix &operator+=(const Matrix<nRows, nCols, T> &rhs);
   // Matrix addition and assignment operator.
   //  rhs     The right hand side Matrix.
   //  return  Assign matrix to the sum of itself and \a rhs matrix.
   // Example: 
   // \code 
   // Matrix<2,2> m1, m2;
   // m1 += m2;
   // \endcode

  inline Matrix &operator-=(const Matrix<nRows, nCols, T> &rhs);
   // Matrix subtraction and assignment operator.
   //  rhs     The right hand side Matrix.
   //  return  Assign matrix to the difference of itself and \a rhs matrix.
   // Example: 
   // \code 
   // Matrix<2,2> m1, m2;
   // m1 -= m2;
   // \endcode

  inline Matrix &operator*=(const T &scalar);
   // Matrix product with scalar and assignment operator.
   //  scalar  The scalar value to be multiplied with the matrix.
   //  return  Assign matrix to the product of itself and \a scalar.
   // Example: 
   // \code 
   // Matrix<2,2> m1;
   // double s;
   // m1 *= s;
   // \endcode

  inline Matrix &operator/=(const T &scalar);
   // Matrix division with scalar and assignment operator.
   //  scalar  The scalar value to divide the matrix by.
   //  return  Assign matrix to the product of itself and \a scalar.
   // Example: 
   // \code 
   // Matrix<2,2> m1;
   // double s;
   // m1 /= s;
   // \endcode

  friend Matrix operator+<>(const Matrix<nRows, nCols, T> &lhs, const Matrix<nRows, nCols, T> &rhs);
   // Matrix addition operator.
   //  lhs     Left hand side matrix
   //  rhs     The right hand side Matrix.
   //  return  The sum of \a rhs and the matrix to the left hand side 
   //          of the addition operator.
   // Example: 
   // \code 
   // Matrix<2,2> m1, m2, m3;
   // m1 = m2 + m3;
   // \endcode

  friend Matrix operator-<>(const Matrix<nRows, nCols, T> &lhs, const Matrix<nRows, nCols, T> &rhs);
   // Matrix difference operator.
   //  lhs     Left hand side matrix
   //  rhs     The right hand side Matrix.
   //  return  The matrix after subtracting \a rhs matrix from the matrix 
   //          on the left hand side of the difference operator.
   // Example: see operator+()

  friend Matrix operator*<>(const Matrix<nRows, nCols, T> &lhs, const T &scalar);
   // Post-multiplication of a matrix with a scalar.
   //  lhs     Left hand side matrix
   //  scalar  The scalar value to be multiplied with the matrix.
   //  return  The product of \a scalar and the matrix.
   // Example: 
   // \code 
   // double s;
   // Matrix<3,2> m1, m2;
   // m1 = m2 * s; 
   // \endcode

  friend Matrix operator*<>(const T &s, const Matrix<nRows, nCols, T> &rhs);
   // Pre-multiplication of a matrix with scalar.
   //  return  The product of \a scalar and \a matrix.
   // Example: 
   // \code 
   // double s;
   // Matrix<3,2> m1, m2;
   // m1 = s * m2; 
   // \endcode

  friend Matrix operator/<>(const Matrix<nRows, nCols, T> &lhs, const T &scalar);
   // Division of a matrix by a scalar.
   //  lhs     Left hand side matrix
   //  scalar  The scalar value to divide the Matrix by.
   //  return  The matrix with each element divided
   //          by the \a scalar.
   // Example: 
   // \code 
   // double s;
   // Matrix<3,2> m1, m2;
   // m1 = m2 / s; 
   // \endcode
   
  friend std::ostream &operator<< <>(std::ostream &output, const Matrix<nRows, nCols, T> &matrix);
   // This function overloads the ostream \c << operator
   // to output the elements of the matrix \a matrix row-wise to the output stream
   // separated by white spaces(e.g. spaces).
   // Example: \code cout << matrix; \endcode

  friend std::istream &operator>> <>(std::istream &input, Matrix<nRows, nCols, T> &matrix);
   // This function overloads the istream \c >> operator
   // to read the elements of the matrix \a matrix from an input stream.
   // The elements must be arranged row-wise in the input stream, separated
   // by white spaces (e.g. spaces, tabs, etc) or comma.
   // Example: \code cin >> matrix; \endcode	

  friend bool operator== <>(const Matrix<nRows, nCols, T> &lhs, const Matrix<nRows, nCols, T> &rhs);
   //  return  'true' if the \a lhs matrix is same as the \a rhs matrix, else FALSE.	

  friend bool operator!= <>(const Matrix<nRows, nCols, T> &lhs, const Matrix<nRows, nCols, T> &rhs);
   //  return  'true' if the \a lhs matrix is not the same as the \a rhs matrix, else FALSE.	

 protected:
  T d_element[nRows * nCols];
  int d_size;
};

//======================================================================== 
// Additional template functions
//======================================================================== 
template<int nCols, int nRows, class T>
Matrix<nCols, nRows, T> transpose(const Matrix<nRows, nCols, T> &matrix);
 //  return The transpose of the matrix \a matrix.

template<int size, class T>
Matrix<size, size, T> inverse(const Matrix<size, size, T> &m);
 // Inverse of a square matrix \a m. This function can be used to 
 // compute inverses of matrices of size 2x2, 3x3, 4x4, 6x6, and 8x8.
 // This library does not support inverse operation on matrices of 
 // any other dimensions.
 //  return  inverse of the matrix m.

template<int size, class T> 
T determinant ( const Matrix <size, size, T> &matrix);
 //  return  Determinant of a matrix.
 
template<int size, class T> 
T trace( const Matrix <size, size, T> &matrix);
 //  return Trace of a size x size matrix.

template<int size, class T>
Matrix<size, size, T> unitMatrix();
 // Generate a unit matrix of size x size.
 // Example: \code Matrix<3,3> A;
 // A=unitMatrix<3>(); \endcode

template<int r1, int c1r2, int c2, class T>
Matrix<r1, c2, T> operator* (const Matrix<r1, c1r2, T> &m1, const Matrix<c1r2, c2, T> &m2);
 // Matrix multiplication.
 //  return The product of \a m1 and \a m2.
 // Example: 
 // \code 
 // Matrix<3,2> m1, m2, m3;
 // m1 = m2 * m3; 
 // \endcode

template<int c1r2, class T>
T operator* (const Matrix<1, c1r2, T> &m1, const Matrix<c1r2, 1, T> &m2);
 // Multiplication between a row Matrix object and a column Matrix.
 //  return  The scalar product of row matrix \a m1 and column matrix \a m2. 

// ========== END OF INTERFACE ==========

//======================================================================== 
// Matrix::Matrix
//========================================================================  
template<int nr, int nc, class T>
Matrix<nr, nc, T>::Matrix(const Matrix<nr, nc, T> &m):MatrixBase<T>()
{
 d_size = nr * nc;
 for (int i = 0; i < d_size; ++i)
  d_element[i] = m.d_element[i];
}	


//======================================================================== 
// Matrix::getElement
//========================================================================  
template<int nr, int nc, class T>
T Matrix<nr, nc, T>::getElement(int r, int c) const
{
 if( (r > nr) || (r < 1) || (c > nc) || (c < 1) )
 {
  static MathException exception;
  exception.setErrorType(QMathException_illegalIndex);
  throw exception;
 }
 return d_element[(r-1) * nc + (c-1)];
}		


//======================================================================== 
// Matrix::setElement
//========================================================================  
template<int nr, int nc, class T>
void Matrix<nr, nc, T>::setElement(int r, int c, T val) 
{
 if( (r > nr) || (r < 1) || (c > nc) || (c < 1) )
 {
  static MathException exception;
  exception.setErrorType(QMathException_illegalIndex);
  throw exception;
 }
 d_element[(r-1) * nc + (c-1)] = val;
}

//======================================================================== 
// Matrix::getColumn
//========================================================================  

template<int nr, int nc, class T>
ColumnVector<nr, T> Matrix<nr, nc, T>::getColumn(int c) const
{
 if( (c > nc) || (c < 1) )
 {
  static MathException exception;
  exception.setErrorType(QMathException_illegalIndex);
  throw exception;
 }
 ColumnVector<nr, T> column;
 int ci = c - 1;
 for (int p = 0; p < nr; ++p)
  column(p+1) = d_element[p * nc + ci];
 return column;
}
 	
 	
//======================================================================== 
// Matrix::getRow
//========================================================================  
template<int nr, int nc, class T>
RowVector<nc, T> Matrix<nr, nc, T>::getRow(int r) const
{	
 if( (r < 1) || (r > nr) )
 {
  static MathException exception;
  exception.setErrorType(QMathException_illegalIndex);
  throw exception;
 }
 
 RowVector<nc, T> row;
 int ri = r - 1;
 for (int p = 0; p < nc; ++p) 
  row(p+1) = d_element[ri * nc + p];
 return row;
}


//======================================================================== 
// Matrix::operator()
//========================================================================  
template<int nr, int nc, class T>
T Matrix<nr, nc, T>::operator()(int r, int c) const
{
 if( (r > nr) || (r < 1) || (c > nc) || (c < 1) )
 {
  static MathException exception;
  exception.setErrorType(QMathException_illegalIndex);
  throw exception;
 }
 return d_element[(r-1) * nc + (c-1)];
}

template<int nr, int nc, class T>
T &Matrix<nr, nc, T>::operator()(int r, int c)
{
 if( (r > nr) || (r < 1) || (c > nc) || (c < 1) )
 {
  static MathException exception;
  exception.setErrorType(QMathException_illegalIndex);
  throw exception;
 }
 return d_element[(r-1) * nc + (c-1)];
}


//======================================================================== 
// Matrix::operator=
//========================================================================  
template<int nr, int nc, class T>
Matrix<nr, nc, T> &Matrix<nr, nc, T>::operator=(const Matrix<nr, nc, T> &m)
{
 if(this != &m) {
  for(int i = 0; i < nr*nc; ++i)
   this->d_element[i] = m.d_element[i];
 }
 return *this;
}


template<int nr, int nc, class T>
MatrixInitializer<T> Matrix<nr, nc, T>::operator=(const T &val)
{
 for (int i = 0; i < d_size; ++i)
  d_element[i] = val;
 MatrixInitializer<T>  matrixInitialize(d_size, 1, d_element);
 return matrixInitialize;
}


//======================================================================== 
// Matrix::operator+
//========================================================================  
template<int nr, int nc, class T>
Matrix<nr, nc, T> &Matrix<nr, nc, T>::operator+=(const Matrix<nr, nc, T> &rhs)
{
 for (int i = 0; i < d_size; ++i)
  d_element[i] += rhs.d_element[i];
 return (*this);
}

template<int nr, int nc, class T>
Matrix<nr, nc, T> operator+(const Matrix<nr, nc, T> &lhs, const Matrix<nr, nc, T> &rhs)
{
 Matrix<nr, nc, T> sum(lhs);
 sum += rhs;
 return (sum);
}


//======================================================================== 
// Matrix::operator-
//========================================================================  
template<int nr, int nc, class T>
Matrix<nr, nc, T> &Matrix<nr, nc, T>::operator-=(const Matrix<nr, nc, T> &rhs)
{
 for (int i = 0; i < d_size; ++i)
  d_element[i] -= rhs.d_element[i];
 return (*this);
}

template<int nr, int nc, class T>
Matrix<nr, nc, T> operator-(const Matrix<nr, nc, T> &lhs, const Matrix<nr, nc, T> &rhs)
{
 Matrix<nr, nc, T> sum(lhs);
 sum -= rhs;
 return (sum);
}


//======================================================================== 
// Matrix::operator*
//========================================================================  
template<int nr, int nc, class T>
Matrix<nr, nc, T> &Matrix<nr, nc, T>::operator*=(const T &s)
{
 for (int i = 0; i < d_size; ++i)
  d_element[i] *= s;
 return (*this);
}

template<int nr, int nc, class T>
Matrix<nr, nc, T> operator*(const Matrix<nr, nc, T> &lhs, const T &s)
{
 Matrix<nr,nc, T> p(lhs);
 p *= s;
 return p;
}

template<int nr, int nc, class T>
Matrix<nr, nc, T> operator*(const T &s, const Matrix<nr, nc, T> &m)
{
 return (m * s);
}

template<int r1, int c1r2, int c2, class T>
Matrix<r1, c2, T> operator* (const Matrix<r1, c1r2, T> &m1, const Matrix<c1r2, c2, T> &m2)
{
 Matrix<r1, c2, T> p;
 T pe;
 for (int r = 1; r <= r1; ++r)
 {
  for (int c = 1; c <= c2; ++c)
  {
   pe = 0;
   for (int com = 1; com <= c1r2; ++com)
    pe += m1.getElement(r, com) * m2.getElement(com, c);
   p(r, c) = pe;
  }
 }
 return p;
}


template<int com, class T>
T operator* (const Matrix<1, com, T> &m1, const Matrix<com,1, T> &m2)
{
 T pe = 0;
 for (int c = 1; c <= com; ++c)
  pe += m1.getElement(1,c) * m2.getElement(c,1);
 return pe;
}


//======================================================================== 
// Matrix::operator/
//========================================================================  
template<int nr, int nc, class T>
Matrix<nr, nc, T> &Matrix<nr, nc, T>::operator/=(const T &s)
{
 if(fabs(s) < 1e-10) // The 'epsilon' here depends on T. 1e-6 for float and 1e-12 for double are good.
 {
  static MathException exception;
  exception.setErrorType(QMathException_divideByZero);
  throw exception;
 }

 for (int i = 0; i < d_size; ++i)
  d_element[i] /= s;
 return (*this);
}

template<int nr, int nc, class T>
Matrix<nr, nc, T> operator/(const Matrix<nr, nc, T> &m, const T &s)
{
 Matrix<nr,nc, T> mat(m);
 mat /= s;
 return mat;
}


//======================================================================== 
// transpose
//========================================================================  
template<int nc, int nr, class T>
Matrix<nc, nr, T> transpose(const Matrix<nr, nc, T> &m)
{
 Matrix<nc, nr, T> t;
 for (int r = 1; r <= nr; ++r)
  for (int c = 1; c <= nc; ++c)
   t(c,r) = m.getElement(r,c);
 return t;
}


//======================================================================== 
// unitMatrix
//========================================================================  
template<int size>
Matrix<size,size,double> unitMatrix()
{
 Matrix<size, size> u;
 for (int r = 1; r <= size; ++r)
  for (int c = 1; c <= size; ++c)
   (r == c) ? (u(r, c) = 1) : (u(r, c) = 0);
 return u;
}


//======================================================================== 
// Matrix::getSubMatrix
//========================================================================  
template<int nr, int nc, class T>
template<int snr, int snc, class X>
void Matrix<nr, nc, T>::getSubMatrix(int pr, int pc, Matrix<snr, snc, X> &sm) const
{
 if( (pr < 1) || (pr > nr) || (pc < 1) || (pc > nc))
 {
  static MathException exception;
  exception.setErrorType(QMathException_illegalIndex);
  throw exception;
 }
 if( (snc > (nc - pc + 1)) || (snr > (nr - pr + 1)) )
 {
  static MathException exception;
  exception.setErrorType(QMathException_incompatibleSize);
  throw exception;
 }
 
 int c;
 int r = pr - 1;
 for (int sr = 1; sr <= snr; ++sr)
 {
  c = pc - 1;
  for (int sc = 1; sc <= snc; ++sc)
  {
   sm(sr, sc) = d_element[r * nc + c];
   ++c;
  }
  ++r;
 }
}


//======================================================================== 
// Matrix::setSubMatrix
//========================================================================  
template<int nr, int nc, class T>
template<int snr, int snc, class X>
void Matrix<nr, nc, T>::setSubMatrix(int pr, int pc, const Matrix<snr, snc, X> &sm)
{
 if( (pr < 1) || (pr > nr) || (pc < 1) || (pc > nc))
 {
  static MathException exception;
  exception.setErrorType(QMathException_illegalIndex);
  throw exception;
 }
 if( (snc > (nc - pc + 1)) || (snr > (nr - pr + 1)) )
 {
  static MathException exception;
  exception.setErrorType(QMathException_incompatibleSize);
  throw exception;
 }
 
 int c;
 int r = pr - 1;
 for (int sr = 1; sr <= snr; ++sr)
 {
  c = pc - 1;
  for (int sc = 1; sc <= snc; ++sc)
  {
   d_element[r * nc + c] = sm.getElement(sr, sc);
   ++c;
  }	
  ++r;
 }
}


//======================================================================== 
// operator<<
//========================================================================  
template<int nr, int nc, class T>
std::ostream &operator<< (std::ostream &out, const Matrix<nr, nc, T> &m)
{
 int i = 0;
 int size = nr * nc;
 while(i < size)
 {
  out << m.d_element[i];
  ++i;
  if(i%nc) out << " ";
  else if(i != size) out << "\n";
 }
 return out;
}


//======================================================================== 
// operator>>
//========================================================================  
template<int nr, int nc, class T>
std::istream &operator>> (std::istream &in, Matrix<nr, nc, T> &m)
{
 int size = nr * nc;
 for(int i = 0; i < size; ++i)
 {
  while((in.peek()=='\n')||(in.peek()=='\r')||(in.peek()==' ')||(in.peek()==','))
   in.ignore(1);
  in >> m.d_element[i];
 }
 return (in);
}					


//======================================================================== 
// operator==
//========================================================================  
template<int nr, int nc, class T>
bool operator==(const Matrix<nr, nc, T> &lhs, const Matrix<nr, nc, T> &rhs)
{
 int size = nr * nc;
 for (int i = 0; i < size; ++i)
  if(lhs.d_element[i] != rhs.d_element[i])
   return false;
 return true;
}


//======================================================================== 
// operator!=
//========================================================================  
template<int nr, int nc, class T>
bool operator!=(const Matrix<nr, nc, T> &lhs, const Matrix<nr, nc, T> &rhs)
{
 if(lhs == rhs)
  return false;
 return true;
}

//======================================================================== 
// inverse
//========================================================================  

template<class T>
Matrix<2, 2, T> inverse( const Matrix<2, 2, T> &m)
{
 T det = determinant(m);
	
 if (fabs(det) < 1e-10)
 {
  static MathException exception;
  exception.setErrorType(QMathException_singular);
  throw exception;
 }
 Matrix<2,2,T> A;
 A(1,1) = m(2,2);
 A(1,2) = -m(1,2);
 A(2,1) = -m(2,1);
 A(2,2) = m(1,1);
 return (A/det);
}

template<class T>
Matrix<3, 3, T> inverse( const Matrix<3, 3, T> &m)
{
 T det = determinant(m);

 if (fabs(det) < 1e-10)
 {
  static MathException exception;
  exception.setErrorType(QMathException_singular);
  throw exception;
 }
 Matrix<3,3,T> A;
 A(1,1) = (m(2,2)*m(3,3)-m(2,3)*m(3,2));
 A(1,2) = -(m(1,2)*m(3,3)-m(1,3)*m(3,2));
 A(1,3) = (m(1,2)*m(2,3)-m(1,3)*m(2,2));
 A(2,1) = -(m(2,1)*m(3,3)-m(2,3)*m(3,1));
 A(2,2) = (m(1,1)*m(3,3)-m(1,3)*m(3,1));
 A(2,3) = -(m(1,1)*m(2,3)-m(1,3)*m(2,1));
 A(3,1) = (m(2,1)*m(3,2)-m(2,2)*m(3,1));
 A(3,2) = -(m(1,1)*m(3,2)-m(1,2)*m(3,1));
 A(3,3) = (m(1,1)*m(2,2)-m(1,2)*m(2,1));
 
 return (A/det);
}
	

template<class T>
Matrix<4, 4, T> inverse( const Matrix<4, 4, T> &m)
{
 T det = determinant(m);

 if (fabs(det) < 1e-10)
 {
  static MathException exception;
  exception.setErrorType(QMathException_singular);
  throw exception;
 }
 Matrix<4,4,T> A;	
 A(1,1) = (m(2,2)*m(3,3)*m(4,4)-m(2,2)*m(3,4)*m(4,3)-m(3,2)*m(2,3)*m(4,4)+m(3,2)*m(2,4)*m(4,3)+m(4,2)*m(2,3)*m(3,4)-m(4,2)*m(2,4)*m(3,3));
 A(1,2) = -(m(1,2)*m(3,3)*m(4,4)-m(1,2)*m(3,4)*m(4,3)-m(3,2)*m(1,3)*m(4,4)+m(3,2)*m(1,4)*m(4,3)+m(4,2)*m(1,3)*m(3,4)-m(4,2)*m(1,4)*m(3,3));
 A(1,3) = (m(1,2)*m(2,3)*m(4,4)-m(1,2)*m(2,4)*m(4,3)-m(2,2)*m(1,3)*m(4,4)+m(2,2)*m(1,4)*m(4,3)+m(4,2)*m(1,3)*m(2,4)-m(4,2)*m(1,4)*m(2,3));
 A(1,4) = -(m(1,2)*m(2,3)*m(3,4)-m(1,2)*m(2,4)*m(3,3)-m(2,2)*m(1,3)*m(3,4)+m(2,2)*m(1,4)*m(3,3)+m(3,2)*m(1,3)*m(2,4)-m(3,2)*m(1,4)*m(2,3));
 A(2,1) = -(m(2,1)*m(3,3)*m(4,4)-m(2,1)*m(3,4)*m(4,3)-m(3,1)*m(2,3)*m(4,4)+m(3,1)*m(2,4)*m(4,3)+m(4,1)*m(2,3)*m(3,4)-m(4,1)*m(2,4)*m(3,3));
 A(2,2) = (m(1,1)*m(3,3)*m(4,4)-m(1,1)*m(3,4)*m(4,3)-m(3,1)*m(1,3)*m(4,4)+m(3,1)*m(1,4)*m(4,3)+m(4,1)*m(1,3)*m(3,4)-m(4,1)*m(1,4)*m(3,3));
 A(2,3) = -(m(1,1)*m(2,3)*m(4,4)-m(1,1)*m(2,4)*m(4,3)-m(2,1)*m(1,3)*m(4,4)+m(2,1)*m(1,4)*m(4,3)+m(4,1)*m(1,3)*m(2,4)-m(4,1)*m(1,4)*m(2,3));
 A(2,4) = (m(1,1)*m(2,3)*m(3,4)-m(1,1)*m(2,4)*m(3,3)-m(2,1)*m(1,3)*m(3,4)+m(2,1)*m(1,4)*m(3,3)+m(3,1)*m(1,3)*m(2,4)-m(3,1)*m(1,4)*m(2,3));
 A(3,1) = (m(2,1)*m(3,2)*m(4,4)-m(2,1)*m(3,4)*m(4,2)-m(3,1)*m(2,2)*m(4,4)+m(3,1)*m(2,4)*m(4,2)+m(4,1)*m(2,2)*m(3,4)-m(4,1)*m(2,4)*m(3,2));
 A(3,2) = -(m(1,1)*m(3,2)*m(4,4)-m(1,1)*m(3,4)*m(4,2)-m(3,1)*m(1,2)*m(4,4)+m(3,1)*m(1,4)*m(4,2)+m(4,1)*m(1,2)*m(3,4)-m(4,1)*m(1,4)*m(3,2));
 A(3,3) = (m(1,1)*m(2,2)*m(4,4)-m(1,1)*m(2,4)*m(4,2)-m(2,1)*m(1,2)*m(4,4)+m(2,1)*m(1,4)*m(4,2)+m(4,1)*m(1,2)*m(2,4)-m(4,1)*m(1,4)*m(2,2));
 A(3,4) = -(m(1,1)*m(2,2)*m(3,4)-m(1,1)*m(2,4)*m(3,2)-m(2,1)*m(1,2)*m(3,4)+m(2,1)*m(1,4)*m(3,2)+m(3,1)*m(1,2)*m(2,4)-m(3,1)*m(1,4)*m(2,2));
 A(4,1) = -(m(2,1)*m(3,2)*m(4,3)-m(2,1)*m(3,3)*m(4,2)-m(3,1)*m(2,2)*m(4,3)+m(3,1)*m(2,3)*m(4,2)+m(4,1)*m(2,2)*m(3,3)-m(4,1)*m(2,3)*m(3,2));
 A(4,2) = (m(1,1)*m(3,2)*m(4,3)-m(1,1)*m(3,3)*m(4,2)-m(3,1)*m(1,2)*m(4,3)+m(3,1)*m(1,3)*m(4,2)+m(4,1)*m(1,2)*m(3,3)-m(4,1)*m(1,3)*m(3,2));
 A(4,3) = -(m(1,1)*m(2,2)*m(4,3)-m(1,1)*m(2,3)*m(4,2)-m(2,1)*m(1,2)*m(4,3)+m(2,1)*m(1,3)*m(4,2)+m(4,1)*m(1,2)*m(2,3)-m(4,1)*m(1,3)*m(2,2));
 A(4,4) = (m(1,1)*m(2,2)*m(3,3)-m(1,1)*m(2,3)*m(3,2)-m(2,1)*m(1,2)*m(3,3)+m(2,1)*m(1,3)*m(3,2)+m(3,1)*m(1,2)*m(2,3)-m(3,1)*m(1,3)*m(2,2));
 return (A/det);
}


template<int size, class T>
Matrix<size, size, T> inverse( const Matrix<size, size, T> &matrix)
{
 if ( (size == 5) || (size == 7) || (size > 8) )
 {
  static MathException exception;
  exception.setErrorType(QMathException_dimensionTooLarge);
  throw exception;
 }

 Matrix<size, size, T> invertedMatrix; 

 if( size == 1)
 {
  invertedMatrix(1,1) = 1.0/matrix(1,1);
  return invertedMatrix;
 }
   
 const int subSize = (int)size/2;
 Matrix<subSize, subSize, T> A1;
 Matrix<subSize, subSize, T> A2;
 Matrix<subSize, subSize, T> A3;
 Matrix<subSize, subSize, T> A4;

 Matrix<subSize, subSize, T> iA1;
 Matrix<subSize, subSize, T> iA2;
 Matrix<subSize, subSize, T> iA3;
 Matrix<subSize, subSize, T> iA4;
	
 matrix.getSubMatrix(1,1,A1);
 matrix.getSubMatrix(1,(subSize+1), A2);
 matrix.getSubMatrix((subSize+1),1,A3);
 matrix.getSubMatrix((subSize+1),(subSize+1),A4);

 iA1 = inverse(A1-(A2*inverse(A4))*A3);
 iA2 = (-1.0)*(inverse(A1)*A2)*(inverse(A4-(A3*inverse(A1))*A2));
 iA3 = (-1.0)*(inverse(A4)*A3)*(inverse(A1-(A2*inverse(A4))*A3));
 iA4 = inverse(A4-(A3*inverse(A1))*A2);

 invertedMatrix.setSubMatrix(1,1,iA1);
 invertedMatrix.setSubMatrix(1,(subSize+1),iA2);
 invertedMatrix.setSubMatrix((subSize+1),1,iA3);
 invertedMatrix.setSubMatrix((subSize+1),(subSize+1),iA4);
 return invertedMatrix;
}


//======================================================================== 
// determinant
//========================================================================  

template<class T> 
T determinant (  const Matrix <2, 2, T> &m)
{
 return ( m(1,1) * m(2,2) - m(2,1) * m(1,2) );
}


template<class T> 
T determinant (  const Matrix <3, 3, T> &m)
{
 return (m(1,1)*m(2,2)*m(3,3)-m(1,1)*m(2,3)*m(3,2)-m(2,1)*m(1,2)*m(3,3)+m(2,1)
 	*m(1,3)*m(3,2)+m(3,1)*m(1,2)*m(2,3)-m(3,1)*m(1,3)*m(2,2));
}

template<class T> 
T determinant (  const Matrix <4, 4, T> &m)
{
 return (m(1,1)*m(2,2)*m(3,3)*m(4,4)-m(1,1)*m(2,2)*m(3,4)*m(4,3)-m(1,1)*m(3,2)*m(2,3)*m(4,4)+m(1,1)*m(3,2)*m(2,4)*m(4,3)+m(1,1)
        *m(4,2)*m(2,3)*m(3,4)-m(1,1)*m(4,2)*m(2,4)*m(3,3)-m(2,1)*m(1,2)*m(3,3)*m(4,4)+m(2,1)*m(1,2)*m(3,4)*m(4,3)+m(2,1)*m(3,2)
	*m(1,3)*m(4,4)-m(2,1)*m(3,2)*m(1,4)*m(4,3)-m(2,1)*m(4,2)*m(1,3)*m(3,4)+m(2,1)*m(4,2)*m(1,4)*m(3,3)+m(3,1)*m(1,2)*m(2,3)
	*m(4,4)-m(3,1)*m(1,2)*m(2,4)*m(4,3)-m(3,1)*m(2,2)*m(1,3)*m(4,4)+m(3,1)*m(2,2)*m(1,4)*m(4,3)+m(3,1)*m(4,2)*m(1,3)*m(2,4)
	-m(3,1)*m(4,2)*m(1,4)*m(2,3)-m(4,1)*m(1,2)*m(2,3)*m(3,4)+m(4,1)*m(1,2)*m(2,4)*m(3,3)+m(4,1)*m(2,2)*m(1,3)*m(3,4)-m(4,1)
	*m(2,2)*m(1,4)*m(3,3)-m(4,1)*m(3,2)*m(1,3)*m(2,4)+m(4,1)*m(3,2)*m(1,4)*m(2,3));
}


template<class T> 
T determinant (  const Matrix <5, 5, T> &m)
{
 return (
m(4,1)*m(3,2)*m(2,3)*m(1,4)*m(5,5)-m(2,1)*m(1,2)*m(3,3)*m(4,4)*m(5,5)+
m(2,1)*m(1,2)*m(3,3)*m(4,5)*m(5,4)+m(2,1)*m(1,2)*m(4,3)*m(3,4)*m(5,5)-
m(2,1)*m(1,2)*m(4,3)*m(3,5)*m(5,4)-m(2,1)*m(1,2)*m(5,3)*m(3,4)*m(4,5)+
m(2,1)*m(1,2)*m(5,3)*m(3,5)*m(4,4)+m(2,1)*m(3,2)*m(1,3)*m(4,4)*m(5,5)-
m(2,1)*m(3,2)*m(1,3)*m(4,5)*m(5,4)-m(2,1)*m(3,2)*m(4,3)*m(1,4)*m(5,5)+
m(2,1)*m(3,2)*m(4,3)*m(1,5)*m(5,4)+m(2,1)*m(3,2)*m(5,3)*m(1,4)*m(4,5)-
m(2,1)*m(3,2)*m(5,3)*m(1,5)*m(4,4)-m(2,1)*m(4,2)*m(1,3)*m(3,4)*m(5,5)+
m(2,1)*m(4,2)*m(1,3)*m(3,5)*m(5,4)+m(2,1)*m(4,2)*m(3,3)*m(1,4)*m(5,5)-
m(2,1)*m(4,2)*m(3,3)*m(1,5)*m(5,4)-m(2,1)*m(4,2)*m(5,3)*m(1,4)*m(3,5)+
m(2,1)*m(4,2)*m(5,3)*m(1,5)*m(3,4)+m(2,1)*m(5,2)*m(1,3)*m(3,4)*m(4,5)-
m(2,1)*m(5,2)*m(1,3)*m(3,5)*m(4,4)-m(2,1)*m(5,2)*m(3,3)*m(1,4)*m(4,5)+
m(2,1)*m(5,2)*m(3,3)*m(1,5)*m(4,4)+m(2,1)*m(5,2)*m(4,3)*m(1,4)*m(3,5)-
m(2,1)*m(5,2)*m(4,3)*m(1,5)*m(3,4)+m(3,1)*m(1,2)*m(2,3)*m(4,4)*m(5,5)-
m(3,1)*m(1,2)*m(2,3)*m(4,5)*m(5,4)-m(3,1)*m(1,2)*m(4,3)*m(2,4)*m(5,5)+
m(3,1)*m(1,2)*m(4,3)*m(2,5)*m(5,4)+m(3,1)*m(1,2)*m(5,3)*m(2,4)*m(4,5)-
m(3,1)*m(1,2)*m(5,3)*m(2,5)*m(4,4)-m(3,1)*m(2,2)*m(1,3)*m(4,4)*m(5,5)+
m(3,1)*m(2,2)*m(1,3)*m(4,5)*m(5,4)+m(3,1)*m(2,2)*m(4,3)*m(1,4)*m(5,5)-
m(3,1)*m(2,2)*m(4,3)*m(1,5)*m(5,4)-m(3,1)*m(2,2)*m(5,3)*m(1,4)*m(4,5)+
m(3,1)*m(2,2)*m(5,3)*m(1,5)*m(4,4)+m(3,1)*m(4,2)*m(1,3)*m(2,4)*m(5,5)-
m(3,1)*m(4,2)*m(1,3)*m(2,5)*m(5,4)-m(3,1)*m(4,2)*m(2,3)*m(1,4)*m(5,5)+
m(3,1)*m(4,2)*m(2,3)*m(1,5)*m(5,4)+m(3,1)*m(4,2)*m(5,3)*m(1,4)*m(2,5)-
m(3,1)*m(4,2)*m(5,3)*m(1,5)*m(2,4)-m(3,1)*m(5,2)*m(1,3)*m(2,4)*m(4,5)+
m(3,1)*m(5,2)*m(1,3)*m(2,5)*m(4,4)+m(3,1)*m(5,2)*m(2,3)*m(1,4)*m(4,5)-
m(3,1)*m(5,2)*m(2,3)*m(1,5)*m(4,4)-m(3,1)*m(5,2)*m(4,3)*m(1,4)*m(2,5)+
m(3,1)*m(5,2)*m(4,3)*m(1,5)*m(2,4)-m(4,1)*m(1,2)*m(2,3)*m(3,4)*m(5,5)+
m(4,1)*m(1,2)*m(2,3)*m(3,5)*m(5,4)+m(4,1)*m(1,2)*m(3,3)*m(2,4)*m(5,5)-
m(4,1)*m(1,2)*m(3,3)*m(2,5)*m(5,4)-m(4,1)*m(1,2)*m(5,3)*m(2,4)*m(3,5)+
m(4,1)*m(1,2)*m(5,3)*m(2,5)*m(3,4)+m(4,1)*m(2,2)*m(1,3)*m(3,4)*m(5,5)-
m(4,1)*m(2,2)*m(1,3)*m(3,5)*m(5,4)-m(4,1)*m(2,2)*m(3,3)*m(1,4)*m(5,5)+
m(4,1)*m(2,2)*m(3,3)*m(1,5)*m(5,4)+m(4,1)*m(2,2)*m(5,3)*m(1,4)*m(3,5)-
m(4,1)*m(2,2)*m(5,3)*m(1,5)*m(3,4)-m(4,1)*m(3,2)*m(1,3)*m(2,4)*m(5,5)+
m(4,1)*m(3,2)*m(1,3)*m(2,5)*m(5,4)-m(4,1)*m(3,2)*m(2,3)*m(1,5)*m(5,4)-
m(4,1)*m(3,2)*m(5,3)*m(1,4)*m(2,5)+m(4,1)*m(3,2)*m(5,3)*m(1,5)*m(2,4)+
m(4,1)*m(5,2)*m(1,3)*m(2,4)*m(3,5)-m(4,1)*m(5,2)*m(1,3)*m(2,5)*m(3,4)-
m(4,1)*m(5,2)*m(2,3)*m(1,4)*m(3,5)+m(4,1)*m(5,2)*m(2,3)*m(1,5)*m(3,4)+
m(4,1)*m(5,2)*m(3,3)*m(1,4)*m(2,5)-m(4,1)*m(5,2)*m(3,3)*m(1,5)*m(2,4)+
m(5,1)*m(1,2)*m(2,3)*m(3,4)*m(4,5)-m(5,1)*m(1,2)*m(2,3)*m(3,5)*m(4,4)-
m(5,1)*m(1,2)*m(3,3)*m(2,4)*m(4,5)+m(5,1)*m(1,2)*m(3,3)*m(2,5)*m(4,4)+
m(5,1)*m(1,2)*m(4,3)*m(2,4)*m(3,5)-m(5,1)*m(1,2)*m(4,3)*m(2,5)*m(3,4)-
m(5,1)*m(2,2)*m(1,3)*m(3,4)*m(4,5)+m(5,1)*m(2,2)*m(1,3)*m(3,5)*m(4,4)+
m(5,1)*m(2,2)*m(3,3)*m(1,4)*m(4,5)-m(5,1)*m(2,2)*m(3,3)*m(1,5)*m(4,4)-
m(5,1)*m(2,2)*m(4,3)*m(1,4)*m(3,5)+m(5,1)*m(2,2)*m(4,3)*m(1,5)*m(3,4)+
m(5,1)*m(3,2)*m(1,3)*m(2,4)*m(4,5)-m(5,1)*m(3,2)*m(1,3)*m(2,5)*m(4,4)-
m(5,1)*m(3,2)*m(2,3)*m(1,4)*m(4,5)+m(5,1)*m(3,2)*m(2,3)*m(1,5)*m(4,4)+
m(5,1)*m(3,2)*m(4,3)*m(1,4)*m(2,5)-m(5,1)*m(3,2)*m(4,3)*m(1,5)*m(2,4)-
m(5,1)*m(4,2)*m(1,3)*m(2,4)*m(3,5)+m(5,1)*m(4,2)*m(1,3)*m(2,5)*m(3,4)+
m(5,1)*m(4,2)*m(2,3)*m(1,4)*m(3,5)-m(5,1)*m(4,2)*m(2,3)*m(1,5)*m(3,4)-
m(5,1)*m(4,2)*m(3,3)*m(1,4)*m(2,5)+m(5,1)*m(4,2)*m(3,3)*m(1,5)*m(2,4)+
(m(2,2)*m(3,3)*m(4,4)*m(5,5)-m(2,2)*m(3,3)*m(4,5)*m(5,4)-m(2,2)*m(4,3)*m(3,4)*m(5,5)+
 m(2,2)*m(4,3)*m(3,5)*m(5,4)+m(2,2)*m(5,3)*m(3,4)*m(4,5)-m(2,2)*m(5,3)*m(3,5)*m(4,4)-
 m(3,2)*m(2,3)*m(4,4)*m(5,5)+m(3,2)*m(2,3)*m(4,5)*m(5,4)+m(3,2)*m(4,3)*m(2,4)*m(5,5)-
 m(3,2)*m(4,3)*m(2,5)*m(5,4)-m(3,2)*m(5,3)*m(2,4)*m(4,5)+m(3,2)*m(5,3)*m(2,5)*m(4,4)+
 m(4,2)*m(2,3)*m(3,4)*m(5,5)-m(4,2)*m(2,3)*m(3,5)*m(5,4)-m(4,2)*m(3,3)*m(2,4)*m(5,5)+
 m(4,2)*m(3,3)*m(2,5)*m(5,4)+m(4,2)*m(5,3)*m(2,4)*m(3,5)-m(4,2)*m(5,3)*m(2,5)*m(3,4)-
 m(5,2)*m(2,3)*m(3,4)*m(4,5)+m(5,2)*m(2,3)*m(3,5)*m(4,4)+m(5,2)*m(3,3)*m(2,4)*m(4,5)-
 m(5,2)*m(3,3)*m(2,5)*m(4,4)-m(5,2)*m(4,3)*m(2,4)*m(3,5)+m(5,2)*m(4,3)*m(2,5)*m(3,4))*m(1,1));
}


template<int size, class T> 
T determinant (  const Matrix <size, size, T> &m)
{
 Matrix<size-1, size-1, T> sm;
 T det;
 int coeff;
 int i, r, c;
 
 det = 0;
 for ( i = 1; i <= size; ++i )
 {
  for ( r = 1; r <= size; ++r )
  {
   for ( c = 2; c <= size; ++c)
   {
    if( r != i )
    {
     if( r < i )
      sm(r, c-1) = m(r, c);
     else
      sm(r-1, c-1)  =  m(r, c);
    }
   }
  }
  (i%2 == 0 ) ? (coeff = -1) : (coeff = 1);
  det += coeff * m(i, 1) * determinant(sm);
 } 									
 return det;
}


//======================================================================== 
// trace
//========================================================================  
template<int size, class T> 
T trace ( const Matrix <size, size, T> &m)
{
 T tr;
 tr = 0;
 for (int i = 1; i <= size; ++i)
  tr += m(i, i);
 return tr;
}


#endif
