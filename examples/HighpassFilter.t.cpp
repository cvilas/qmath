//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : HighpassFilter.t.cpp
// Description          : Example program for the high-pass filter class.
//========================================================================  

#include "HighpassFilter.hpp"
#include <math.h>
#include <stdio.h>

//========================================================================
// HighpassFilter.t.cpp
//------------------------------------------------------------------------
// Demonstration of high-pass filtering of a signal with multiple
// frequency components to extract the high frequency component. 
//========================================================================

// If using GNUC makefile, just compile main function here. If using 
// MS Visual C++, the main function is in examples_main.cpp
#if defined(__GNUC__)
    #define test_HighpassFilter(argc, argv) main(argc, argv)
#endif

int test_HighpassFilter(int argc, char **argv)
{
 double wn = 600;	       // cut-off freq. in Hz
 double dirtySignal;           // signal with multiple frequencies
 double filteredSignal;        // filtered signal
 FILE *outfile;                // file to store results
 double p = 0;

 // Define filter, with a sampling period as the second argument.
 HighpassFilter<double> myFilter(wn, 0.000142857);

 myFilter.initializeFilter(p, p);
 outfile = fopen("HighpassFilter.dat", "w+");

 fprintf(outfile, "%s\n%s %s\n", "%Highpass filter output file",
         "%dirty_signal", "filtered_signal" );
 for (int i=0; i<1000; i++)
 {
  // generate signal with 1Hz, 60Hz and 700Hz components
  p = ((double)i)/7000.0; 
  dirtySignal = 2 +  sin(2*M_PI*p/10.0) + sin(60*2.0*M_PI*p) + sin(700*2.0*M_PI*p);
  
  // filter off low frequency compoments to extract 700Hz component
  filteredSignal = myFilter.filter(dirtySignal);

  //simply write the outputs to a file...
  fprintf(outfile, "%f %f\n", dirtySignal, filteredSignal);
 }

 fclose(outfile);

 return(0);
}

