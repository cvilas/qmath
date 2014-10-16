//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : Adams3Integrator.t.cpp
// description          : Example program for the Integrator.
//========================================================================

//========================================================================
// Adams3Integrator.t.cpp
//------------------------------------------------------------------------
// Integrates a trignometric function using Adams method, and compares 
// result with analytical integration.
//========================================================================

#include "Adams3Integrator.hpp"
#include "ColumnVector.hpp"

#include <stdio.h>
#include <math.h>
#ifndef M_PI
 #define M_PI 3.14159265358979323846
#endif

// If using GNUC makefile, just compile main function here. If using 
// MS Visual C++, the main function is in examples_main.cpp
#if defined(__GNUC__)
    #define test_Adams3Integrator(argc, argv) main(argc, argv)
#endif

int test_Adams3Integrator(int argc, char **argv)
{
 FILE *outfile;                           // File to store results
 double velocity;                         // some data
 double position_adams;                   // numerical integral
 double position_actual;                  // actual integral
 double initValue;                        // initial value of integration
 double sampling_period;                  // sampling period
 Adams3Integrator< double > myIntegrator; // numerical integrator

 outfile = fopen("Adams3Integrator.dat", "w+");
 initValue = 0;
 sampling_period = 0.001;
 
 myIntegrator.setSamplingPeriod(sampling_period);
 myIntegrator.reset(initValue);
 
 fprintf(outfile, "%s\n%s %s %s\n", "%Adams 3rd order integrator output file",
         "%velocity", "position_adams", "position_actual" );
 for (int i=0; i<1000; i++)
 {
  // input data
  velocity = sin(2*M_PI*i*sampling_period);
  
  // integrate
  position_adams = myIntegrator.integrate(velocity);
  position_actual = 1.0/(2*M_PI) * (1 - cos(2*M_PI*i*sampling_period));

  // simply write the outputs to a file... 
  fprintf(outfile, "%f %f %f\n", velocity, position_adams, position_actual);
 }
 
 fclose(outfile);
 return(0);
}
