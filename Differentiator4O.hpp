//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : Differentiator4O.hpp
// Description          : Template class for 4th order numerical differentiation
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

#ifndef INCLUDED_Differentiator4O_hpp
#define INCLUDED_Differentiator4O_hpp

#include "Differentiator.hpp"

//====================================================================
// class Differentiator4O
// -------------------------------------------------------------------
// \brief
// Fourth order differentation followed by low-pass filtering. 
//
// <b>Example Program:</b>
// \include Differentiator4O.t.cpp
//========================================================================  
 
template<class T = double>
class Differentiator4O : public Differentiator<T>
{
 public:
  inline Differentiator4O(double period = 0.001);
   // The Constructor initializes.
   // The cut-off frequency is set to half the
   // sampling frequency and damping ratio of the
   // low-pass filter in the differentiator is set to 1. 
   //  period  The sampling period of the 
   //          differentiator in seconds.
	
  virtual ~Differentiator4O (){}
   // The default destructor.

  void reset();
   // Resets the differentiator output to zero.

  virtual T differentiate(const T &input);
   // This function implements the numerical 
   // method for differentiation.
   // The output in the first cycle is smoothened to zero.
   //  input  The present value of the 
   //         variable being differentiated.
		
 // ========== END OF INTERFACE ==========
 
 private:
  T d_oldInput[3];
};



//==============================================================
// End of declarations.
//==============================================================


//======================================================================== 
// Differentiator4O::Differentiator
//========================================================================  
template<class T>
Differentiator4O<T>::Differentiator4O(double samplingPeriod)
 : Differentiator<T>(samplingPeriod)
{
 d_oldInput[0] = 0;
 d_oldInput[1] = 0;
 d_oldInput[2] = 0;
}


//======================================================================== 
// Differentiator4O::reset
//========================================================================  
template<class T>
void Differentiator4O<T>::reset()
{
 Differentiator<T>::reset();
 d_oldInput[0] = 0;
 d_oldInput[1] = 0;
 d_oldInput[2] = 0;
}


//======================================================================== 
// Differentiator4O::differentiate
//========================================================================  
template<class T>
T Differentiator4O<T>::differentiate(const T &currentInput)
{
 static int order = 1;
 if (this->d_initialize)
 {
  this->d_previousInput = currentInput;
  d_oldInput[0] = 0;
  d_oldInput[1] = 0;
  d_oldInput[2] = 0;
  this->d_lowPassFilter.setAutoInit();
  this->d_initialize = false;
  order = 1;
 }
	
 T filteredOutput;
 switch(order)
 {
  case(1):
   this->d_currentDifferential 
    = (1.0/this->d_samplingPeriod) 
    * (currentInput - this->d_previousInput);
   ++order;
  break;
  case(2):
   this->d_currentDifferential 
    = (1.0/(2.0 * this->d_samplingPeriod)) 
    * (3.0 * currentInput - 4.0 * this->d_previousInput 
    + d_oldInput[0]);
   ++order;
  break;
  case(3):
   this->d_currentDifferential 
    = (1.0/(6.0 * this->d_samplingPeriod)) 
    * (11.0 * currentInput - 18.0 * this->d_previousInput 
    + 9.0 * d_oldInput[0] - 2.0 * d_oldInput[1]);
   ++order;
  break;
  default:
   this->d_currentDifferential 
    = (1.0/(12.0 * this->d_samplingPeriod)) 
    * (25.0 * currentInput - 48.0 * this->d_previousInput 
    + 36.0 * d_oldInput[0] - 16.0 * d_oldInput[1] + 3.0 * d_oldInput[2]);
  break;
 }
 d_oldInput[2] = d_oldInput[1];
 d_oldInput[1] = d_oldInput[0];
 d_oldInput[0] = this->d_previousInput;
 this->d_previousInput = currentInput;

 if(this->d_useFilter)
  filteredOutput = this->d_lowPassFilter.filter(
                   this->d_currentDifferential);
 else
  filteredOutput = this->d_currentDifferential;
 
 return filteredOutput;
}


#endif
