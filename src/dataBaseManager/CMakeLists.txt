# CMakeLists.txt file for the dataBaseManagerLib library:
# ======================================================
set(libName "dataBaseManagerLib")

add_library(${libName} lib1.cpp)

# Currently this library (object) does not depend on any other module/object
# in the project. When it changes, add here what needed.
# target_link_libraries(${libName} <some_dependent_lib>)



#SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
#SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
#SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

target_compile_options(${libName} PUBLIC -g -O0 -Wall -fprofile-arcs -ftest-coverage)
target_link_options(${libName} PUBLIC -fprofile-arcs -ftest-coverage)

message(STATUS "CMakeLists.txt of ${libName} - created library")

