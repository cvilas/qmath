//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : LowpassFilter.hpp
// Description          : Template class for 2nd order low pass filter
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


#ifndef INCLUDED_LOWPASSFILTER_HPP
#define INCLUDED_LOWPASSFILTER_HPP

#include <math.h>
#ifndef M_PI
 #define M_PI 3.14159265358979323846
#endif

//=============================================================================
// class LowpassFilter
//-----------------------------------------------------------------------------
// \brief
// A second order butterworth lowpass filter. 
//
// <b>Example Program:</b>
// \include LowpassFilter.t.cpp
//=============================================================================

template<class T = double>
class LowpassFilter
{
 public:
  LowpassFilter(double hz = 1, double period = 0.001, 
                double damp = 1);
   // This constructor for the filter initializes the parameters of the filter.
   //  hz      The cut-off frequency in \a hertz (default is 1).
   //  period  The sampling period in seconds (default is 1ms).
   //  damp    Desired damping ratio (default is 1).
	
  ~LowpassFilter(){}
   // The default destructor.

  inline void setCutOffFrequencyHz(double hz);
   // This function sets the cut-off frequency of the filter in \a hertz. 
	
  inline void setCutOffFrequencyRad(double rads);
   // This function sets the cut-off frequency of the filter in \a rad/s. 

  inline double getCutOffFrequencyHz() const;
   //  return  The cut-off frequency of the filter in \a hertz.

  inline double getCutOffFrequencyRad() const;
   //  return  The cut-off frequency of the filter in \a rad/s.

  inline void setDampingRatio(double damp);
   // Sets the damping factor of the butterworth filter.
 
  inline double getDampingRatio() const;
   //  return The damping factor of the filter.

  inline void setSamplingPeriod(double period);
   // Sets the sampling period of the low-pass filter. 
 
  inline double getSamplingPeriod() const;
   //  return  The sampling period in seconds.

  inline void setAutoInit();
   // Automatic initialization of the filter.

  inline void initializeFilter (T &initInput, T &initOutput);
   // Initializes the initial value of input and output.
   //  initInput   Initial value of the input to the filter.
   //  initOutput  Initial output of the filter.

  T filter(const T &input);
   // The filter.

protected:
 double d_samplingPeriod;
 double d_cutOffFrequencyHz;
 double d_cutOffFrequencyRad;
 double d_dampingRatio;
 double d_numeratorParameter[3]; 
 double d_denumParameter[3];
 int d_initFlag ;
 T d_previousInputX[3];  
 T d_previousOutputY[3];
 T d_numerator;
 T d_denumerator;
 T d_filteredOut;
 
 void calculateInternalParameters();	
  // Calculates the internel parameters based 
  // on user inputs of cut-off frequency, etc.

  // ========== END OF INTERFACE ==========
}; 



//============================================================
// End of Declarations.
//============================================================


//============================================================
// LowpassFilter::LowpassFilter
//============================================================
template<class T>
LowpassFilter<T>::LowpassFilter (double cutOffFrequencyHz, double samplingPeriod,
				 double dampingFactor)     
{
 // set class parameters
 d_cutOffFrequencyHz = cutOffFrequencyHz;
 d_dampingRatio = dampingFactor;
 d_samplingPeriod = samplingPeriod;
 d_cutOffFrequencyRad = 2 * M_PI * d_cutOffFrequencyHz;

 //calculate the filter parameters
 calculateInternalParameters();
 d_initFlag = 1;
}


//============================================================
// LowpassFilter::setCutOffFrequencyHz
//============================================================
template<class T>
void LowpassFilter<T>::setCutOffFrequencyHz(double cutOffFrequencyHz)
{
 d_cutOffFrequencyHz = cutOffFrequencyHz;
 d_cutOffFrequencyRad = 2 * M_PI * d_cutOffFrequencyHz;
 calculateInternalParameters();
}


//============================================================
// LowpassFilter::setCutOffFrequencyRad
//============================================================
template<class T>
void LowpassFilter<T>::setCutOffFrequencyRad(double cutOffFrequencyRad)
{
 d_cutOffFrequencyRad = cutOffFrequencyRad;
 d_cutOffFrequencyHz = 	d_cutOffFrequencyRad/(2 * M_PI);
 calculateInternalParameters();
}


//============================================================
// LowpassFilter::getCutOffFrequencyHz
//============================================================
template<class T>
double LowpassFilter<T>::getCutOffFrequencyHz() const
{
 return(d_cutOffFrequencyHz);
}


//============================================================
// LowpassFilter::getCutOffFrequencyRad
//============================================================
template<class T>
double LowpassFilter<T>::getCutOffFrequencyRad() const
{
 return(d_cutOffFrequencyRad);
}


//============================================================
// LowpassFilter::setDampingRatio
//============================================================
template<class T>
void LowpassFilter<T>::setDampingRatio(double dampingRatio)
{
 d_dampingRatio = dampingRatio;
 calculateInternalParameters();
}


//============================================================
// LowpassFilter::getDampingRatio
//============================================================
template<class T>
double LowpassFilter<T>::getDampingRatio() const
{
 return(d_dampingRatio);
}


//============================================================
// LowpassFilter::setSamplingPeriod
//============================================================
template<class T>
void LowpassFilter<T>::setSamplingPeriod(double samplingPeriod)
{
 d_samplingPeriod = samplingPeriod;
 calculateInternalParameters();
}


//============================================================
// LowpassFilter::getSamplingPeriod
//============================================================
template<class T>
double LowpassFilter<T>::getSamplingPeriod() const
{
 return(d_samplingPeriod);
}


//============================================================
// LowpassFilter::setAutoInit
//============================================================
template<class T>
void LowpassFilter<T>::setAutoInit()
{
 d_initFlag = 1;
}


//============================================================
// LowpassFilter::initializeFilter
//============================================================
template<class T>
void LowpassFilter<T>::initializeFilter (T &initInput, T &initOutput)
{
 for (int i=0; i<3; ++i)
 {
  d_previousInputX[i] = initInput;
  d_previousOutputY[i] = initOutput;
 }
 d_initFlag = 0;
}


//============================================================
// LowpassFilter::calculateInternalParameters
//============================================================
template<class T>
void LowpassFilter<T>::calculateInternalParameters()
{
 d_numeratorParameter[0] = d_cutOffFrequencyRad * d_cutOffFrequencyRad;
 d_numeratorParameter[1] = 2 * d_numeratorParameter[0];
 d_numeratorParameter[2] = d_numeratorParameter[0];

 // denum. parameter calculations
 d_denumParameter[0] = d_numeratorParameter[0]
                     + 4 * d_cutOffFrequencyRad * d_dampingRatio / d_samplingPeriod
                     + 4 / (d_samplingPeriod * d_samplingPeriod);

 d_denumParameter[1] = d_numeratorParameter[1]
                     - 8 / (d_samplingPeriod * d_samplingPeriod);

 d_denumParameter[2] = d_numeratorParameter[0]
                     - 4 * d_cutOffFrequencyRad * d_dampingRatio / d_samplingPeriod
                     + 4 / (d_samplingPeriod * d_samplingPeriod) ;
}


//============================================================
// LowpassFilter::filter
//============================================================
template<class T>
T LowpassFilter<T>::filter (const T &input)
{
 // automatic initialization 	
 if (d_initFlag ==1 )
 {
  for (int i=0; i<3; ++i)
  { 
   d_previousInputX[i] = input;
   d_previousOutputY[i] = input;
  }
  d_initFlag = 0;	
 }
	
 d_previousInputX[0] = input;
 // calculate the input related part and assign it to numerator
 d_numerator = d_numeratorParameter[0] * d_previousInputX[0]
             + d_numeratorParameter[1] * d_previousInputX[1]
             + d_numeratorParameter[2] * d_previousInputX[2];
 d_denumerator = d_denumParameter[1] * d_previousOutputY[1]
               + d_denumParameter[2] * d_previousOutputY[2];
 d_previousOutputY[0] = (d_numerator - d_denumerator) / d_denumParameter[0];
 d_filteredOut = d_previousOutputY[0];

 // and shift the input and output values for the next cycle
 d_previousOutputY[2] =  d_previousOutputY[1] ;
 d_previousOutputY[1] =  d_previousOutputY[0] ;
 d_previousInputX[2] =  d_previousInputX[1] ;
 d_previousInputX[1] =  d_previousInputX[0] ;

 return (d_filteredOut);
}


# endif
