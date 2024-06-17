# CMakeLists.txt file for the communication library:
# ==================================================
set(libName "communicationLib")

add_library(${libName} SHARED socketBase.cpp datagramSocket.cpp)

target_compile_options(${libName} PUBLIC -g -O0 -Wall -fprofile-arcs -ftest-coverage)
target_link_options(${libName} PUBLIC -fprofile-arcs -ftest-coverage)

message(STATUS "CMakeLists.txt of ${libName} - created library")

