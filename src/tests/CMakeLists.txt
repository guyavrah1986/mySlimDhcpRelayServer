# CMakeLists.txt for the unit tests:
# =================================

message(STATUS "unit tests CMakeLists.txt of ${CMAKE_PROJECT_NAME}")
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/src/utilities/cpp11ThreadWrapper/include")
 
# Link runTests with what we want to test and the GTest and pthread library
find_library(GTEST_LIBRARY gtest HINTS /usr/lib)
message(STATUS "GTEST_INCLUDE_DIRS is: ${GTEST_INCLUDE_DIRS}")
message(STATUS "GTEST_LIBRARY is: ${GTEST_LIBRARY}")
message(STATUS "GTEST_LIBRARIES is: ${GTEST_LIBRARIES}")

set(testsExeName "unitTestsExe.out")
add_executable(${testsExeName} unitTestsMain.cpp)

# Due to the fact that the tcmalloc is installed into a "non standra" location
# adding here an "extra" location for the linker to look for libraries. Note
# that under these additional path(s) the linker ONLY looks for libraries 
# with names according to the convention, for example:libtcmalloc.so 
# If there is NOT a single file like so under the below path, the linker will
# report an error in this case.
link_directories(/usr/lib/x86_64-linux-gnu)


# NOTES:
# tcmalloc - is linked in order to use tcmalloc in the unit tests instead of glibc malloc - only
# for the sake of using the heap checker feature of the tcmalloc library.
target_link_libraries(${testsExeName} ${GTEST_LIBRARY} tcmalloc cpp11ThreadWrapperLib pthread)
