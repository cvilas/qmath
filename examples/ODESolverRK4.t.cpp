//======================================================================== 
// Package		: QMath - Template Math Library
// Authors		: Vilas Kumar Chitrakaran (vilas@ieee.org)
// Compatibility	: GCC 2.95.3 and above, MSVS 2005
// File                 : ODESolverRK4.t.cpp
// Description          : Example program for the ODESolverRK4 integrator.
//========================================================================

#include <stdio.h>
#include <math.h>
#include "ODESolverRK4.hpp"
#include "Vector.hpp"


//========================================================================
// This program computes solution of a 2nd order differential equation
// numerically and compares result with analytical solution.
//========================================================================


//========================================================================
// Physical system - an mass-spring-damper.
// This function implements physical system as x' = f(x,t)
//========================================================================
Vector<2> system(Vector<2> &y, double t)
{
 Vector<2> ydot;
 t = t;
 double M = 1.0;  // mass (kg)
 double K = 10.0; // spring stiffness coefficient (N/m)
 double f = 2.0;  // viscous friction coefficient (Ns/m)
	
 // system: mx'' + fx' + Kx = 0.
 // Write in state space form as
 // [y1dot; y2dot] = [-f/M, -K/M; 1, 0].[y1; y2]
	
 ydot(1) = -(f/M) * y(1)  - (K/M) * y(2);
 ydot(2) = y(1);
	
 return ydot;
}


//========================================================================
// main function
//========================================================================
// If using GNUC makefile, just compile main function here. If using 
// MS Visual C++, the main function is in examples_main.cpp
#if defined(__GNUC__)
    #define test_ODESolverRK4(argc, argv) main(argc, argv)
#endif

int test_ODESolverRK4(int argc, char **argv)
{
 FILE *outfile;
 double dt = 0.001;                // sampling time (s)
 Vector<2> y;		           // state vector ([velocity; position])
 Vector<2> y_next_numerical;       // numerical soln at next time step
 double y_next_analytical;         // analytical soln at next time step
 ODESolverRK4< Vector<2> > solver; // numerical solver
	
 y = 2.0, 4.0; // initial velocity and position
		
 // set up the solver
 solver.setODE(system);
 solver.setSamplingPeriod(dt);
 solver.reset(y);
	
 outfile = fopen("ODESolverRK4.dat", "w+");

 // Call integrate() every time-step 
 double t = 0;
 double error;
  
 y_next_numerical = y;
 y_next_analytical = y(2);
 fprintf(outfile, "%s\n%s %s %s\n", "%ODE Solver RK4 output file",
         "%analytical_output", "numerical_output", "error" );
 for(t = dt; t < 10.0; t +=dt)
 {
  // find error between analytical and numerical soln.
  error = y_next_analytical - y_next_numerical(2);

  // dump outputs in file
  fprintf(outfile, "%f %f %f\n", y_next_analytical, y_next_numerical(2), error);
  
  // analytical (actual) solution
  y_next_analytical = exp(-t)*(4*cos(3 * t) + 2 * sin(3 * t));
	 	
  // numerical solution
  y_next_numerical = solver.stepSolve();
 }
	
 fclose(outfile);
 return(0);
}


