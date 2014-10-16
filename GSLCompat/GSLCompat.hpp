//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : GSLCompat.hpp
// Description          : Conversion between QMath types and GSL types
//
// Copyright (C) 2000 Vilas Chitrakaran
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or (at
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

#ifndef INCLUDED_GSLCompat_hpp
#define INCLUDED_GSLCompat_hpp 

#ifdef QMATH_DLL
 #ifdef QMATH_DLL_EXPORT
  #define QMATHDLL_API __declspec(dllexport)
 #else
  #define QMATHDLL_API __declspec(dllimport)
 #endif
#else
 #define QMATHDLL_API
#endif

#include "Vector.hpp"
#include "gsl_matrix.h"
#include "gsl_vector.h"

/*! Prototypes for typecasting to GSL data types. Note that the
    functions do not copy data between objects. Hence, changes made to 
    contents of one type will reflect in the contents of the converted
    type. Supported data types:
    char, unsigned char, short, unsigned short, int, unsigned int, long,  
    unsigned long, float, double, long double.
*/

QMATHDLL_API void GSLCompat_matrix(MatrixBase<double> *q, gsl_matrix *gsl);
 /*!< Obtain a gsl_matrix pointer from a Matrix pointer for
      data type double. Subsequent modification of one object
      will be reflected in the other.
      \param q    A pointer to QMath object
      \param gsl  A pointer to GSL object
 */
 
QMATHDLL_API void GSLCompat_matrix(MatrixBase<char> *q, gsl_matrix_char *gsl);
QMATHDLL_API void GSLCompat_matrix(MatrixBase<unsigned char> *q, gsl_matrix_uchar *gsl);
QMATHDLL_API void GSLCompat_matrix(MatrixBase<short> *q, gsl_matrix_short *gsl);
QMATHDLL_API void GSLCompat_matrix(MatrixBase<unsigned short> *q, gsl_matrix_ushort *gsl);
QMATHDLL_API void GSLCompat_matrix(MatrixBase<int> *q, gsl_matrix_int *gsl);
QMATHDLL_API void GSLCompat_matrix(MatrixBase<unsigned int> *q, gsl_matrix_uint *gsl);
QMATHDLL_API void GSLCompat_matrix(MatrixBase<long> *q, gsl_matrix_long *gsl);
QMATHDLL_API void GSLCompat_matrix(MatrixBase<unsigned long> *q, gsl_matrix_ulong *gsl);
QMATHDLL_API void GSLCompat_matrix(MatrixBase<float> *q, gsl_matrix_float *gsl);
QMATHDLL_API void GSLCompat_matrix(MatrixBase<long double> *q, gsl_matrix_long_double *gsl);
 
QMATHDLL_API void GSLCompat_vector(VectorBase<double> *q, gsl_vector *gsl);
 /*!< Obtain an gsl_vector pointer from a Vector pointer for
      data type double. Subsequent modification of one object
      will be reflected in the other.
      \param q    A pointer to QMath object
      \param gsl  A pointer to GSL object
 */
 
QMATHDLL_API void GSLCompat_vector(VectorBase<char> *q, gsl_vector_char *gsl);
QMATHDLL_API void GSLCompat_vector(VectorBase<unsigned char> *q, gsl_vector_uchar *gsl);
QMATHDLL_API void GSLCompat_vector(VectorBase<short> *q, gsl_vector_short *gsl);
QMATHDLL_API void GSLCompat_vector(VectorBase<unsigned short> *q, gsl_vector_ushort *gsl);
QMATHDLL_API void GSLCompat_vector(VectorBase<int> *q, gsl_vector_int *gsl);
QMATHDLL_API void GSLCompat_vector(VectorBase<unsigned int> *q, gsl_vector_uint *gsl);
QMATHDLL_API void GSLCompat_vector(VectorBase<long> *q, gsl_vector_long *gsl);
QMATHDLL_API void GSLCompat_vector(VectorBase<unsigned long> *q, gsl_vector_ulong *gsl);
QMATHDLL_API void GSLCompat_vector(VectorBase<float> *q, gsl_vector_float *gsl);
QMATHDLL_API void GSLCompat_vector(VectorBase<long double> *q, gsl_vector_long_double *gsl);

#endif // INCLUDED_GSLCompat_hpp 
