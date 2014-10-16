#======================================================================== 
# Package	:Math Library
# Authors	: Vilas kumar Chitrakaran  
# Start Date	: Wed Dec 20 11:06:55 GMT 2000
# ----------------------------------------------------------------------  
# File: makefile (makefile of examples)
#========================================================================  

usegsl=no
LDFLAGS = g++ -W -Wall -fexceptions -O2 -g -o
INCLUDEHEADERS = -I ../ -I /usr/local/include -I /usr/qrts/include
INCLUDELIB = -L ../ -lQMath
TARGETS = LowpassFilter.t HighpassFilter.t \
		Differentiator.t Differentiator4O.t Integrator.t \
		Matrix.t Vector.t Transform.t \
		MathException.t ODESolverRK4.t Adams3Integrator.t
targets:	$(TARGETS)
CLEAN = rm -rf $(TARGETS) *.dat *.o


# ----- LowpassFilter -----
LowpassFilter.t :	LowpassFilter.t.cpp
	$(LDFLAGS) $@ $? $(INCLUDEHEADERS) $(INCLUDELIB)

# ----- HighpassFilter -----
HighpassFilter.t :	HighpassFilter.t.cpp
	$(LDFLAGS) $@ $? $(INCLUDEHEADERS) $(INCLUDELIB)

# ----- Differentiator -----
Differentiator.t :	Differentiator.t.cpp
	$(LDFLAGS) $@ $? $(INCLUDEHEADERS) $(INCLUDELIB)

# ----- Differentiator4O -----
Differentiator4O.t :	Differentiator4O.t.cpp
	$(LDFLAGS) $@ $? $(INCLUDEHEADERS) $(INCLUDELIB)

# ----- Integrator -----
Integrator.t :	Integrator.t.cpp
	$(LDFLAGS) $@ $? $(INCLUDEHEADERS) $(INCLUDELIB)

# ----- Matrix -----
Matrix.t :	Matrix.t.cpp
	$(LDFLAGS) $@ $? $(INCLUDEHEADERS) $(INCLUDELIB)

# ----- Adams3Integrator -----
Adams3Integrator.t :	Adams3Integrator.t.cpp
	$(LDFLAGS) $@ $? $(INCLUDEHEADERS) $(INCLUDELIB)

# ----- ODESolverRK4 -----
ODESolverRK4.t :	ODESolverRK4.t.cpp
	$(LDFLAGS) $@ $? $(INCLUDEHEADERS) $(INCLUDELIB)

# ----- Vector-----
Vector.t :	Vector.t.cpp
	$(LDFLAGS) $@ $? $(INCLUDEHEADERS) $(INCLUDELIB)

# ----- Transform-----
Transform.t :	Transform.t.cpp
	$(LDFLAGS) $@ $? $(INCLUDEHEADERS) $(INCLUDELIB)

# ----- MathException-----
MathException.t :	MathException.t.cpp
	$(LDFLAGS) $@ $? $(INCLUDEHEADERS) $(INCLUDELIB)

clean:
	@$(CLEAN)

