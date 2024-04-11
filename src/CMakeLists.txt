# CMakeLists.txt file for the main application (executable)
# =========================================================

set(exeName "myHttpServer.out")

message(STATUS "CMakeLists.txt of ${exeName} executable")

# Add the executable which is of now, composed ONLY from the main.cpp
add_executable(${exeName} main.cpp)

# Link the executable with all relevant libraries
target_link_libraries(${exeName} PUBLIC infraLib dataBaseManagerLib)

# For test covrage:
target_compile_options(${exeName} PUBLIC -g -O0 -Wall -fprofile-arcs -ftest-coverage)
target_link_options(${exeName} PUBLIC -fprofile-arcs -ftest-coverage)

# Add the binary tree to the search path for include files
# so that we will find sampleObj1.h
target_include_directories(${exeName} PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/src/infra/include"
                          "${PROJECT_SOURCE_DIR}/src/cacheManager/include"
                          )
