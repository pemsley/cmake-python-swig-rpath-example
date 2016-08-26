
FIND_PACKAGE(SWIG REQUIRED)
FIND_PACKAGE(PythonLibs)

INCLUDE(${SWIG_USE_FILE})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

# we want to make a shared library libtriv_stats.dylib that 
# is compiled from sources stats.cc (standard CMake usage)
#
ADD_LIBRARY(triv_stats SHARED stats.cc)

# libtriv_stats.dylib depends on the maths library (standard 
# CMake usage)
#
TARGET_LINK_LIBRARIES(triv_stats "m")

# stats.i include C++ header - so tell SWIG that it should 
# compile in C++ mode
#
SET_SOURCE_FILES_PROPERTIES(stats.i PROPERTIES CPLUSPLUS ON)

# running swig on stats.i makes the python module simple_module (see how
# simple_module is used in test.py) - I use "simple_module" but
# I could have equally have used "stats" (I'd have to mirror that 
# change in test.py)
#
SWIG_ADD_MODULE(simple_module python stats.i)

# the python module simple_module wraps the class and function
# of stats.hh/.cc - and the library for that compiled code is
# libtriv_stats.dylib
#
SWIG_LINK_LIBRARIES(simple_module triv_stats ${PYTHON_LIBRARIES})

if (APPLE) 

   # interesting reading: https://blog.kitware.com/upcoming-in-cmake-2-8-12-osx-rpath-support/

   # INSTALL_NAME_DIR overrides MACOSX_RPATH.  Try not to do that.

   # this sets the install_name of libtriv_stats.dylib as @rpath/libtriv_stats.dylib
   SET_TARGET_PROPERTIES(triv_stats PROPERTIES MACOSX_RPATH TRUE)
   SET_TARGET_PROPERTIES(triv_stats PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
   
   # Use rpath for _simple_module.so
   SET_TARGET_PROPERTIES(_simple_module PROPERTIES MACOSX_RPATH TRUE)

   # append directories in the linker search path and outside the project to the INSTALL_RPATH
   SET_TARGET_PROPERTIES(_simple_module PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

   # this is where libtriv_stats.dylib is installed relative to where _simple_module.so is installed
   SET_TARGET_PROPERTIES(_simple_module PROPERTIES INSTALL_RPATH "@loader_path/../../..")

else()

   SET_TARGET_PROPERTIES(_simple_module PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
   SET_TARGET_PROPERTIES(_simple_module PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

endif()

INSTALL(TARGETS triv_stats DESTINATION lib)
INSTALL(TARGETS _simple_module DESTINATION lib/python2.7/site-packages)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/simple_module.py DESTINATION lib/python2.7/site-packages)
