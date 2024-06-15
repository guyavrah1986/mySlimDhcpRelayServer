# CMakeLists.txt file for the cpp11ThreadWrapper library
# ======================================================
set(libName "infraLib")
include(../../globalDefines.cmake)
add_library(${libName} SHARED cpp11ThreadWrapper.cpp 
                              posixCpp11ThreadWrapper.cpp)

# In order to use the C++11 <thread> one needs to link against
# the respective "system threading library". The project intendent
# to run on Linux machine, so link to pthread.
target_link_libraries(${libName} pthread)

message("BUILD_UNIT_TESTS=${BUILD_UNIT_TESTS}")
if( BUILD_UNIT_TESTS ) 
    message("BUILD_UNIT_TESTS evaluates to True")
    target_compile_options(${libName} PUBLIC ${unit_tests_compile_options})
    target_link_options(${libName} PUBLIC ${unit_tests_link_options})
    message(STATUS "setting additional compiler flags for unit testing:${unit_tests_compile_options}")
    message(STATUS "setting additional linker flags for unit testing:${unit_tests_link_options}")
endif()

message(STATUS "End of CMakeLists.txt of ${libName} - library was created!")