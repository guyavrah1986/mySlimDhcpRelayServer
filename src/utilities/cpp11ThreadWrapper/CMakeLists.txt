# CMakeLists.txt file for the cpp11ThreadWrapper library
# ======================================================
set(libName "cpp11ThreadWrapperLib")

message(STATUS "CMakeLists.txt of ${libName} library")

add_library(${libName} cpp11ThreadWrapper.cpp)
