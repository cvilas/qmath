//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : MathException.hpp
// Description          : Template class for runtime exception handling
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

#ifndef INCLUDED_MathException_hpp
#define INCLUDED_MathException_hpp

#ifdef QMATH_DLL
 #ifdef QMATH_DLL_EXPORT
  #define QMATHDLL_API __declspec(dllexport)
 #else
  #define QMATHDLL_API __declspec(dllimport)
 #endif
#else
 #define QMATHDLL_API
#endif

//======================================================================== 
/*! \enum _QMathException 
    \brief Supported exception types */
//======================================================================== 
typedef enum _QMathException
{
 QMathException_unknown             = 0x00,  //!< Undocumented error.
 QMathException_illegalIndex        = 0x01,  //!< Illegal index.
 QMathException_singular            = 0x02,  //!< Singular matrix (determinant < 1e-10).
 QMathException_divideByZero        = 0x03,  //!< Division by number less than 1e-10.
 QMathException_incompatibleSize    = 0x04,  /*!< Operation between two 
                                                  non-conformable matrices. */
 QMathException_typeMismatch        = 0x05,  /*!< Operation between incompatible 
                                                  data types (Ex: int and double). */
 QMathException_dimensionTooLarge   = 0x06   /*!< Matrix dimensions too large for 
                                                  the library to handle (Ex:
                                                  calling inverse() on matrices 
                                                  larger than 8 x 8.) */
}QMathException_t;


static struct 
{
 QMathException_t error;
 const char *errorMsg;
}QMathExceptions[] = 
{
 { QMathException_unknown,           "Math Exception : Unknown Exception"},
 { QMathException_illegalIndex,      "Math Exception : Index out of range"},
 { QMathException_singular,          "Math Exception : Singular Matrix."},
 { QMathException_divideByZero,      "Math Exception : Division by zero."},
 { QMathException_incompatibleSize,  "Math Exception : Operation between objects of incompatible sizes."},
 { QMathException_typeMismatch,      "Math Exception : Operation between objects of incompatible types."},
 { QMathException_dimensionTooLarge, "Math Exception : Matrix too large."}
};

//======================================================================== 
// class MathException
// ----------------------------------------------------------------------
// \brief
// Run-time exception handling for the math library. 
//
// The error type is internally set by the library.
//
// <b>Example Program:</b>
// \include MathException.t.cpp
//========================================================================  
class QMATHDLL_API MathException
{
 public:
  inline MathException() {d_errorType = QMathException_unknown;};
  ~MathException(){}
  inline const char *getErrorMessage() const; 
  inline QMathException_t getErrorType() const;
  inline bool isErrorType(QMathException_t error);
  inline void setErrorType(QMathException_t error);
  // ========== END OF INTERFACE ==========
 private:
  QMathException_t d_errorType;
};

//==========================================================
// End of declarations.
//==========================================================


//==========================================================
// MathException::isErrorType
//==========================================================
bool MathException::isErrorType(QMathException_t error)
{
 return (d_errorType == error);
}

//==========================================================
// MathException::getErrorType
//==========================================================
QMathException_t MathException::getErrorType() const
{
 return d_errorType;
}

//==========================================================
// MathException::getErrorMessage
//==========================================================
const char *MathException::getErrorMessage() const
{
 return QMathExceptions[d_errorType].errorMsg;
}

//==========================================================
// MathException::setErrorType
//==========================================================
void MathException::setErrorType(QMathException_t error)
{
 d_errorType = error;
}

#endif

