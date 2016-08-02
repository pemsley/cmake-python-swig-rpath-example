
FIND_PACKAGE(SWIG REQUIRED)
FIND_PACKAGE(PythonLibs)

INCLUDE(${SWIG_USE_FILE})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

ADD_LIBRARY(triv_stats SHARED stats.cc)

TARGET_LINK_LIBRARIES(triv_stats "m")

SET_SOURCE_FILES_PROPERTIES(stats.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(simple_module python stats.i)

SWIG_LINK_LIBRARIES(simple_module triv_stats ${PYTHON_LIBRARIES})

if (APPLE) 

   # interesting reading: https://blog.kitware.com/upcoming-in-cmake-2-8-12-osx-rpath-support/

   # INSTALL_NAME_DIR overrides MACOSX_RPATH.  Try not to do that.


   # this sets the install_name of libtriv_stats.dylib as @rpath/libtriv_stats.dylib
   SET_TARGET_PROPERTIES(triv_stats PROPERTIES MACOSX_RPATH TRUE)
   SET_TARGET_PROPERTIES(triv_stats PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

   
   SET_TARGET_PROPERTIES(_simple_module PROPERTIES MACOSX_RPATH TRUE)

   SET_TARGET_PROPERTIES(_simple_module PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

   SET_TARGET_PROPERTIES(_simple_module PROPERTIES INSTALL_RPATH "@loader_path/../../..")

else()

   SET_TARGET_PROPERTIES(_simple_module PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
   SET_TARGET_PROPERTIES(_simple_module PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

endif()

INSTALL(TARGETS triv_stats DESTINATION lib)
INSTALL(TARGETS _simple_module DESTINATION lib/python2.7/site-packages)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/simple_module.py DESTINATION lib/python2.7/site-packages)


