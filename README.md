# myHttpServer
C++ based multi threaded slim HTTP server

# Initial development environment requierments
- `git` should be installed
- `cmake` should be installed
- Currently the development environment is Ubuntu22.04.
- install GTEST: 
* `sudo apt-get install libgtest-dev`
* `cd /usr/src/gtest`
-- `sudo cmake CMakeLists.txt`
-- `sudo make`
-- `sudo cp lib/*.a /usr/lib`
- Install `google-perftools` and `libgoogle-perftools-dev`
* sudo apt-get install google-perftools libgoogle-perftools-dev
-- The libgoogle-perftools-dev is for the gperftools/heap-checker.h.

# Build instructions:
- `cd myHttpServer` (root folder of the project)
- Create the "out of source" `build` folder: `mkdir build`
- `cd build`
- `build$ cmake ../`
- `build$ make` (it will build according to the Makefile that is present there - main artifcat is `myHttpServer.out`)

# Run unit tests:
- After sucessfully building the project, the unit tests (GTest based) will be built as well.
- To run ALL the unit tests: `build$ src/tests/unitTestsExe.out`
- Run a specific unit test: `build$ src/tests/unitTestsExe.out --gtest_filter=sampleObjectTest.createSingleMySampleObject`
- Run unit test with tcmalloc's heap leak detection enabled: `build$ env HEAPCHECK=local src/tests/unitTestsExe.out --gtest_filter=sampleObjectTest.createSingleMySampleObject`
