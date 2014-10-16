//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : Differentiator.hpp
// Description          : Template class for numerical differentiation
//                        using backward difference
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

#ifndef INCLUDED_Differentiator_hpp
#define INCLUDED_Differentiator_hpp

#include "LowpassFilter.hpp"
#include <math.h>
#ifndef M_PI
 #define M_PI 3.14159265358979323846
#endif

//====================================================================
// class Differentiator
// -------------------------------------------------------------------
// \brief
// This is the base class for differentiators.
//
// This class implements numerical differentation using backward 
// difference followed by low-pass filtering. 
//
// The Differentiator performs numerical differentiation of a signal 
// using backward difference, followed by smoothening of the 
// differentiated signal by a 2nd order butterworth low pass filter. 
// The filtering is usually required due to the noisy nature of the 
// result of numerical differentiation. Unfortunately low pass filter 
// also introduces lag and innacuracy to the result. Filtering action 
// should be disabled using disableFilter() if your input signal is 
// sufficiently smooth.
//
// A derived class from Differentiator can override the differenting 
// algorithm provided.The class \c Differentiator can be used with many 
// data types (double, int, RowVector, ColumnVector, Matrix, etc).
// 
// <b>Example Program:</b>
// \include Differentiator.t.cpp
//========================================================================  
 
template<class T = double>
class Differentiator
{
 public:
  inline Differentiator(double period = 0.001);
   // The Constructor initializes. The low pass filter is
   // enabled by default, the cut-off frequency is set to half the
   // sampling frequency and damping ratio of the
   // low-pass filter in the differentiator is set to 1. 
   //  period  The sampling period of the 
   //          differentiator in seconds.
	
  virtual ~Differentiator (){}
   // The default destructor.

  inline void setSamplingPeriod(double period);
   // Sets the sampling period of the differentiator 

  inline void setCutOffFrequencyHz(double f);
   // Differentiation is followed by a low pass filtering process.
   // This function sets the cut-off frequency of the filter in \a hertz. 

  inline void setCutOffFrequencyRad(double cutOffFrequencyRad);
   // Differentiation is followed by a low pass filtering process.
   // This function sets the cut-off frequency of the filter in \a rad/sec. 

  inline void setDampingRatio(double d);
   // Sets the damping factor of the butterworth filter.

  void disableFilter();
   // Disable the low pass filtering after the 
   // differentiation. (Low pass filter is enabled
   // by default.)

  void enableFilter();
   // Enable the low pass filtering after the 
   // differentiation.

  void reset();
   // Resets the differentiator output to zero.

  virtual T differentiate(const T &input);
   // This function implements the numerical 
   // method for differentiation. The user can derive
   // a different method of differentiation in a 
   // derived class. The differentiator
   // output in the first cycle is smoothened to zero.
   //  input  The current value of the 
   //         signal being differentiated.
		
 // ========== END OF INTERFACE ==========
 
 protected:
  double d_samplingPeriod;
  T d_previousInput;
  T d_currentDifferential;
  LowpassFilter<T> d_lowPassFilter;
  bool d_initialize;
  bool d_useFilter;
};



//==============================================================
// End of declarations.
//==============================================================


//======================================================================== 
// Differentiator::Differentiator: Constructor of the Differentiator class
//========================================================================  
template<class T>
Differentiator<T>::Differentiator(double samplingPeriod)
{
 setSamplingPeriod(samplingPeriod);
 setDampingRatio(1);
 setCutOffFrequencyHz(1.0/(2.0*samplingPeriod));
 d_previousInput = 0;
 d_initialize = true;
 d_useFilter = true;
}


//======================================================================== 
// Differentiator::setSamplingPeriod
//========================================================================  
template<class T>
void Differentiator<T>::setSamplingPeriod(double p)
{
 d_samplingPeriod = p; 
 d_lowPassFilter.setSamplingPeriod(d_samplingPeriod);
}


//======================================================================== 
// Differentiator::setDampingRatio
//========================================================================  
template<class T>
void Differentiator<T>::setDampingRatio(double d) 
{
 d_lowPassFilter.setDampingRatio(d);
}


//======================================================================== 
// Differentiator::disableFilter
//========================================================================  
template<class T>
void Differentiator<T>::disableFilter()
{
 d_useFilter = false;
}


//======================================================================== 
// Differentiator::enableFilter
//========================================================================  
template<class T>
void Differentiator<T>::enableFilter()
{
 d_useFilter = true;
}


//======================================================================== 
// Differentiator::setCutOffFrequencyHz
//========================================================================  
template<class T>
void Differentiator<T>::setCutOffFrequencyHz(double cutOffFrequencyHz)
{
 d_lowPassFilter.setCutOffFrequencyHz(cutOffFrequencyHz);
}


//======================================================================== 
// Differentiator::setCutOffFrequencyRad
//========================================================================  
template<class T>
void Differentiator<T>::setCutOffFrequencyRad(double cutOffFrequencyRad)
{
 d_lowPassFilter.setCutOffFrequencyRad(cutOffFrequencyRad);
}


//======================================================================== 
// Differentiator::reset
//========================================================================  
template<class T>
void Differentiator<T>::reset()
{
 d_initialize = true;
}


//======================================================================== 
// Differentiator::differentiate
//========================================================================  
template<class T>
T Differentiator<T>::differentiate(const T &currentInput)
{
 if (d_initialize)
 {
  d_previousInput = currentInput;
  d_lowPassFilter.setAutoInit();
  d_initialize = false;
 }
	
 T filteredOutput;

 d_currentDifferential = (currentInput - d_previousInput) * (1/d_samplingPeriod) ;
 d_previousInput = currentInput;

 if(d_useFilter)
  filteredOutput = d_lowPassFilter.filter(d_currentDifferential);
 else
  filteredOutput = d_currentDifferential;
 
 return filteredOutput;
}


#endif
