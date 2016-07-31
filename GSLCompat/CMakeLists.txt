
set(LIBQMATHGSL_SRC 
	GSLCompat.cpp)

set(LIBQMATHGSL_HDR
	GSLCompat.hpp)

include_directories("${PROJECT_SOURCE_DIR}")


# get GSL package
FIND_PACKAGE(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIRS} ${GSLCBLAS_INCLUDE_DIRS})
set (EXTRA_LIBS ${EXTRA_LIBS} QMathGSL ${GSL_LIBRARIES} ${GSLCBLAS_LIBRARIES})

# add the library target
add_library(qmathgsl_dynamic SHARED ${LIBQMATHGSL_SRC})
add_library(qmathgsl_static STATIC ${LIBQMATHGSL_SRC})
set_target_properties(qmathgsl_dynamic PROPERTIES OUTPUT_NAME "QMathGSL")
set_target_properties(qmathgsl_dynamic PROPERTIES VERSION ${QMATH_VERSION_MAJOR}.${QMATH_VERSION_MINOR} SOVERSION ${QMATH_VERSION_MAJOR})
set_target_properties(qmathgsl_static PROPERTIES OUTPUT_NAME "QMathGSL")

set(CMAKE_CXX_FLAGS "-W -Wall -fexceptions -fno-builtin -O2 -fpic -D_REENTRANT -g")

# add the install targets
install(TARGETS qmathgsl_dynamic qmathgsl_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install (FILES ${LIBQMATHGSL_HDR} DESTINATION include)

