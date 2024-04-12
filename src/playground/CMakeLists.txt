# CMakeLists.txt file for the playgroundLib library:
# =================================================
set(libName "playgroundLib")
add_library(${libName} playground.cpp)
include(../../globalDefines.cmake)

message("BUILD_UNIT_TESTS=${BUILD_UNIT_TESTS}")
if( BUILD_UNIT_TESTS ) 
    message("BUILD_UNIT_TESTS evaluates to True")
    target_compile_options(${libName} PUBLIC ${unit_tests_compile_options})
    target_link_options(${libName} PUBLIC ${unit_tests_link_options})
    message(STATUS "setting additional compiler flags for unit testing:${unit_tests_compile_options}")
    message(STATUS "setting additional linker flags for unit testing:${unit_tests_link_options}")
endif()

message(STATUS "End of CMakeLists.txt of ${libName} - created library")

