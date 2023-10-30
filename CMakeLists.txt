# This is the project's main CMakeLists.txt
#========================================== 

cmake_minimum_required(VERSION 3.5)

# Add/customize global project settings:
project(myHttpServer)
message(STATUS "main CMakeLists.txt of ${CMAKE_PROJECT_NAME}")
set(CMAKE_CXX_STANDARD 17)
message(STATUS "main CMakeLists.txt of ${CMAKE_PROJECT_NAME} - the PROJECT_SOURCE_DIR is set to:${PROJECT_SOURCE_DIR}")

# In case the application is to be built as a 32-bit application, un-comment the below
#set(CMAKE_CXX_FLAGS "-m32")

include_directories(src)

add_subdirectory(src)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/utilities/cpp11ThreadWrapper)

#add_subdirectory(test)
