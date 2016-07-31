include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "-W -Wall -fexceptions -fno-builtin -O2 -fpic -D_REENTRANT -g")
set(LINK_DIR ${PROJECT_BINARY_DIR}/lib)

link_directories(${LINK_DIR})
if (ENABLE_GSL)
	link_directories(${LINK_DIR} ${PROJECT_BINARY_DIR}/GSLCompat/)
endif (ENABLE_GSL)

set(TARGET_EXE
	Adams3Integrator.t
	Differentiator4O.t
	Differentiator.t
	HighpassFilter.t
	Integrator.t
	LowpassFilter.t
	MathException.t
	Transform.t
	Vector.t
	ODESolverRK4.t
	Matrix.t)

foreach(target ${TARGET_EXE})
	add_executable(${target} ${target}.cpp) 
	target_link_libraries( ${target} qmath_static)
endforeach(target)

if (ENABLE_GSL)
	set(TARGET_EXE ${TARGET_EXE} GSLCompat.t)
	add_executable(GSLCompat.t ${PROJECT_SOURCE_DIR}/GSLCompat/GSLCompat.t.cpp)
	link_directories(${LINK_DIR} ${PROJECT_BINARY_DIR}/GSLCompat/lib)
	target_link_libraries( GSLCompat.t qmath_static qmathgsl_static ${GSL_LIBRARIES} ${GSLCBLAS_LIBRARIES} )
endif (ENABLE_GSL)

# add the install targets
install(TARGETS ${TARGET_EXE} DESTINATION bin)

