//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : GSLCompat.t.cpp
// Description          : Example program for the GSL compatibility.
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

//========================================================================
// GSLCompat.t.cpp
//------------------------------------------------------------------------
// This program demonstrates how a QMath object can be typecast as a 
// GSL type.
//========================================================================

#include "GSLCompat.hpp"
#include <iostream>
#ifdef _MSC_VER
 #include <conio.h>
#endif

using namespace std;

int main(int argc, char **argv)
{
 gsl_matrix gsl_mat;  //GSL objects
 gsl_vector gsl_vec;
 Matrix<2,3> q_mat;   // QMath objects
 Vector<3> q_vec;

 // prepare a gsl_matrix pointer from Matrix
 GSLCompat_matrix(&q_mat, &gsl_mat); 
 
 // prepare a gsl_vector pointer from Vector
 GSLCompat_vector(&q_vec, &gsl_vec);
 
 // Modify QMath objects
 q_mat = 0, 1, 2, 
         3, 4, 5;
 
 q_vec = 7, 8, 9;

 // The above modifications will be reflected in
 // GSL objects. Now you are free to use all
 // GSL algorithms on this object...
 cout << "gsl_vector: ";
 for (int i = 0; i < 3; i++)
  cout << gsl_vector_get(&gsl_vec, i) << " ";
 cout << endl;

 cout << "gsl_matrix: ";
 for(int i = 0; i < 2; i++)
 {
  for(int j = 0; j < 3; j++) 
   cout << gsl_matrix_get(&gsl_mat, i, j) << " ";
  cout << endl;
 }
 cout << endl << "Press any key to exit";
#ifdef _MSC_VER
	_getch();
#endif

 return 0;
}
