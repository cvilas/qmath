QMath
=====

QMath is a matrix library (C++ template classes) for robotic applications. This library is primarily for UNIX systems. Note: I wrote this library in 2006 when working towards a masters degree in Robotics; hence, most of the classes here are quite dated. You will be better served by other open-source libraries today, for instance, Eigen (http://eigen.tuxfamily.org/). This repository is mostly for my own reference.


Introduction
------------

QMath provides a set of C++ template classes for matrices, vectors, homogeneous transformations, numerical filtering, integration and differentiation. It is a real-time capable library with an intuitive programming interface resembling MATLAB. Although it is a completely independant package by itself, it was originally developed as the math library for the Robotic Platform, and significantly simplifies programming for robotic applications. QMath cannot be compared to general purpose scientific computation and numerical libraries such as the GNU Scientific Library and LAPACK, which provide much more extensive functionality. This is a simple, light-weight and extensible library of math functions commonly used in robotics.

The library uses templates of the data type and dimensions (e.g. number of rows and columns in a matrix). The use of templates and inline functions produce highly optimized code that is almost as fast in execution as direct programming. The size of QMath data types used in a program are known at compile time: there is no run time dynamic memory allocation which can risk the loss of deterministic real-time response.

The following classes/data types are provided by the library:

- MatrixBase: Pure virtual base class for matrices.
- VectorBase: Pure virtual base class for vectors.
- Matrix: The class for matrices.
- RowVector: A class for row vectors (1 x n matrices).
- ColumnVector: A class for column vectors (n x 1 matrices).
- Vector: Same as ColumnVector.
- Transform: Homogeneous transformations.
- LowpassFilter: 2nd order low pass butterworth filter.
- HighpassFilter: 2nd order high pass filter.
- Integrator: Base class for integrators. Provides trapezoidal integration method.
- Adams3Integrator: Integrator using Adams 3rd order method.
- ODESolverRK4: Solver for ordinary differential equations using 4th order Runge-Kutta method.
- Differentiator: Base class for differentiators. Computes derivative using backward difference.
- Differentiator4O: 4th order differentiator.

Inter-operability with GNU Scientific Library (Added Sept. 2005)
-----------------------------------------------------------------

A new header file GSLCompat.hpp has been added to the library. This allows conversion of QMath Matrix and Vector types to GSL types gsl_matrix and gsl_vector, respectively, without any performance penalty (again, no dynamic memory allocations are used). Functions declared in this file can be used to map a QMath type to GSL type object, and subsequently use GSL library functions to perform computations. This is useful, for example, when you want to compute the SVD of a matrix, or solve linear equations. To use this functionality, you must install GSL. (For QNX 6.2.1, here is a version of GSL that I know compiles without problems: gsl-1.8.tar.gz).

Building
--------
The library was developed for UNIX using GCC compiler. However with the script provided in the win directory, the library can be compiled for Windows using Visual C++ version 7.0 and up. Compile will fail for earlier versions of VC++ due to lack of proper support for C++ templates.

Applications
------------

- Robot kinematics and control.
- Realtime applications.

References
----------

- Jack W. Crenshaw, "MATH Toolkit for REAL-TIME Programming," CMP Books, ISBN: 1929629095, 2000.
- Lonnie C. Ludeman, "Fundamentals of Digital Signal Processing," Harper & Row, ISBN: 0060440937, 1986.



