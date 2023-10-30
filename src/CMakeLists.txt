# CMakeLists.txt file for the main application (executable)
# =========================================================

set(exeName "myHttpServer.out")

message(STATUS "CMakeLists.txt of ${exeName} executable")

# Add the executable which is of now, composed ONLY from the main.cpp
add_executable(${exeName} main.cpp)

target_link_libraries(${exeName} PUBLIC cpp11ThreadWrapperLib)

# Add the binary tree to the search path for include files
# so that we will find sampleObj1.h
target_include_directories(${exeName} PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/src/utilities/cpp11ThreadWrapperLib/include"
                          )
