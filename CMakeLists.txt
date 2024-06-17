# This is the project's main CMakeLists.txt
#========================================== 
cmake_minimum_required(VERSION 3.22.1)

# Add/customize global project settings:
project(myHttpServer)
set(CMAKE_CXX_STANDARD 20)

message(STATUS "main CMakeLists.txt of ${CMAKE_PROJECT_NAME}")
message(STATUS "The root (top level) folder of the project is:${PROJECT_SOURCE_DIR}")

# Help CMake find relevant files for the Log4cxx logger package
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
find_package(Log4cxx REQUIRED)

message(STATUS "main CMakeLists.txt of ${CMAKE_PROJECT_NAME}")
message(STATUS "The root folder of the project is:${PROJECT_SOURCE_DIR}")

# Add the following compilation settings (flags) globally to ALL targets
# in this project
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

include_directories(src)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/infra)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/communication)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/tests)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/playground)

add_subdirectory(src)