# CMakeLists.txt file for the hash table library:
# ===============================================
set(libName "hashTableLib")
include(../../globalDefines.cmake)

# TODO: According to the user preference the source that will
# be used for the implementation of the hash table will be 
# either the std::unordered_map OR some user defined implementation
# in either C or C++. 
# Add here a condition to check which source files should be added.
file(GLOB HASH_TABLE_LIB_SRC ./*.c)
add_library(${libName} SHARED ${HASH_TABLE_LIB_SRC})

message("BUILD_UNIT_TESTS=${BUILD_UNIT_TESTS}")
if( BUILD_UNIT_TESTS ) 
    message("BUILD_UNIT_TESTS evaluates to True")
    target_compile_options(${libName} PUBLIC ${unit_tests_compile_options})
    target_link_options(${libName} PUBLIC ${unit_tests_link_options})
    message(STATUS "setting additional compiler flags for unit testing:${unit_tests_compile_options}")
    message(STATUS "setting additional linker flags for unit testing:${unit_tests_link_options}")
endif()

message(STATUS "End of CMakeLists.txt of ${libName} - library was created!")