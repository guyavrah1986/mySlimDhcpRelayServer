# This is the project's main CMakeLists.txt
#========================================== 

cmake_minimum_required(VERSION 3.5)

project(myHttpServer)

message(STATUS "main CMakeLists.txt of ${CMAKE_PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 17)

# In case the application is to be built as a 32-bit application, un-comment the below
#set(CMAKE_CXX_FLAGS "-m32")

include_directories(src)

add_subdirectory(src)

#add_subdirectory(sampleObj1Lib)

#add_subdirectory(test)
