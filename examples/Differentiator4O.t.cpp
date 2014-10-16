//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : Differentiator4O.t.cpp
// Description          : Example program for the Differentiator4O.
//========================================================================

//========================================================================
//Differentiator4O.t.cpp
//------------------------------------------------------------------------
// Demonstration of Differentiator class. The numerical differentiation
// result is compared with analytical solution.
//========================================================================

#include "Differentiator4O.hpp"
#include "ColumnVector.hpp"
#include <stdio.h>

// If using GNUC makefile, just compile main function here. If using 
// MS Visual C++, the main function is in examples_main.cpp
#if defined(__GNUC__)
    #define test_Differentiator4O(argc, argv) main(argc, argv)
#endif

int test_Differentiator4O(int argc, char **argv)
{
 FILE *outfile;  // This file holds the input and output waveforms.
 outfile = fopen("Differentiator4O.dat", "w+");
 
 double input;             // input signal
 double output_numerical;  // numerically computed derivative
 double output_actual;     // analytically computed derivative
 double error;             // error between numerical and analytical results
 double samplingPeriod;
 
 // Create Differentiator with a sampling period of 1 milli-second.
 samplingPeriod = 0.001;
 Differentiator4O<double> differentiator(samplingPeriod);
 
 // Set filter parameters.
 differentiator.setCutOffFrequencyHz(500);
 differentiator.setDampingRatio(1);
 differentiator.reset();

 fprintf(outfile, "%s\n%s %s %s %s\n", "%Differentiator output file",
         "%input", "output_actual", "output_numerical", "error" );
 for (int i = 0; i < 1.0/samplingPeriod; i++)
 {	
  input = cos(2*M_PI*i*samplingPeriod); // 1 Hz signal

  // Differentiate analytically and numerically
  output_actual = -(2 * M_PI) * sin(2*M_PI*i*samplingPeriod);
  output_numerical = differentiator.differentiate(input); 
  
  error = output_actual - output_numerical;
  
  // write the outputs to a file... 
  fprintf(outfile, "%f %f %f %f\n", input, output_actual, output_numerical, error);
 }
 fclose(outfile);
 return(0);
}


