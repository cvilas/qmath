//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : LowpassFilter.t.cpp
// Description          : Example program for the high-pass filter class.
//========================================================================  


//========================================================================
// LowpassFilter.t.cpp
//------------------------------------------------------------------------
// Demonstration of low-pass filtering of a noisy sine wave signal. 
//========================================================================

#include "LowpassFilter.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


 
// If using GNUC makefile, just compile main function here. If using 
// MS Visual C++, the main function is in examples_main.cpp
#if defined(__GNUC__)
    #define test_LowpassFilter(argc, argv) main(argc, argv)
#endif

int test_LowpassFilter(int argc, char **argv)
{
 double wn = 3;            //cutoff frequency in hertz.
 double damp =1.0;         // damping ratio
 double dirtySignal;       // noisy signal
 double filteredSignal;    // filtered signal
 double p = 0;
 FILE *outfile;

 //define Filter
 LowpassFilter<double>  velocityFilter (wn, 0.001, damp);
 velocityFilter.initializeFilter(p, p);
 
 outfile = fopen("LowpassFilter.dat", "w+");

 fprintf(outfile, "%s\n%s %s\n", "%Lowpass filter output file",
         "%dirty_signal", "filtered_signal" );
 for (int i=0; i<1000; i++)
 {
  // generate sine wave corrupted by random noise
  p = ((double)i)/1000.0;
  dirtySignal = sin(2*M_PI*p) + ((double)rand()/(double)RAND_MAX) - 0.5;
  
  // filter the data
  filteredSignal = velocityFilter.filter(dirtySignal);
  
  // simply write the outputs to a file... 
  fprintf(outfile, "%f %f\n", dirtySignal, filteredSignal);
 }

 fclose(outfile);
 return(0);
}
