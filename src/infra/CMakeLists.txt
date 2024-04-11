# CMakeLists.txt file for the cpp11ThreadWrapper library
# ======================================================
set(libName "infraLib")
include(../../globalDefines.cmake)
add_library(${libName} cpp11ThreadWrapper.cpp)

# In order to use the C++11 <thread> one needs to link against
# the respective "system threading library". The project intendent
# to run on Linux machine, so link to pthread.
target_link_libraries(${libName} pthread)

message(STATUS "setting additional compiler flags for unit testing:${unit_tests_compile_options}")
message(STATUS "setting additional linker flags for unit testing:${unit_tests_link_options}")
target_compile_options(${libName} PUBLIC ${unit_tests_compile_options})
target_link_options(${libName} PUBLIC ${unit_tests_link_options})

message(STATUS "CMakeLists.txt of ${libName} - created library")