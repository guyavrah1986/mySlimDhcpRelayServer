# CMakeLists.txt file for the main application (executable)
# =========================================================
set(exeName "myHttpServer.out")
include(../globalDefines.cmake)
message(STATUS "CMakeLists.txt of ${exeName} executable")

# Add the executable which is of now, composed ONLY from the main.cpp
add_executable(${exeName} main.cpp)

# Link the executable with all relevant libraries
target_link_libraries(${exeName} PUBLIC infraLib dataBaseManagerLib)

# For test covrage:
message(STATUS "setting additional compiler flags for unit testing:${unit_tests_compile_options}")
message(STATUS "setting additional linker flags for unit testing:${unit_tests_link_options}")
target_compile_options(${exeName} PUBLIC ${unit_tests_compile_options})
target_link_options(${exeName} PUBLIC ${unit_tests_link_options})

# Add the binary tree to the search path for include files
# so that we will find sampleObj1.h
target_include_directories(${exeName} PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/src/infra/include"
                          "${PROJECT_SOURCE_DIR}/src/cacheManager/include"
                          )
