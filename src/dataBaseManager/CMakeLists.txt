# CMakeLists.txt file for the dataBaseManagerLib library:
# ======================================================
set(libName "dataBaseManagerLib")

add_library(${libName} lib1.cpp)

# Currently this library (object) does not depend on any other module/object
# in the project. When it changes, add here what needed.
# target_link_libraries(${libName} <some_dependent_lib>)

message(STATUS "CMakeLists.txt of ${libName} - created library")

