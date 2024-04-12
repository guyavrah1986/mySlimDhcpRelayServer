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
- Install `lcov`: `sudo apt-get update install lcov` (version used: 1.14)

# Build instructions:
- `cd myHttpServer` (root folder of the project)
- Create the "out of source" `build` folder: `mkdir build`
- `cd build`
- `build$ cmake ../ -DBUILD_UNIT_TESTS=True` (for debug/unit test/ non production mode)
- `build$ make` (it will build according to the Makefile that is present there - main artifcat is `myHttpServer.out`)

# Run unit tests:
- After sucessfully building the project, the unit tests (GTest based) will be built as well.
- To run ALL the unit tests: `build$ src/tests/unitTestsExe.out`
- Run a specific unit test: `build$ src/tests/unitTestsExe.out --gtest_filter=sampleObjectTest.createSingleMySampleObject`
- Run unit test with tcmalloc's heap leak detection enabled: `build$ env HEAPCHECK=local src/tests/unitTestsExe.out --gtest_filter=sampleObjectTest.createSingleMySampleObject`
- Generating unit test covrage: 
-- Run the unit tests (as described above)
-- From the `build` folder run: `lcov –c –d . –o testsCovrage.info`
-- Then generate the HTML report: `genhtml testsCovrage.info`
-- Several files will be added to current folder, out of which the `index.html` file will have the unit tests covrage report

# Application covarage:
- Build the application (according to the build instructions mentioned above)
- Run the application: `cd myHttpServer/build/src && ./myHttpServer/build` 
- Go to the `myHttpServer/build/src/CMakeFiles/myHttpServer.out.dir` there you will find the `main.cpp.gcda` and `main.cpp.gcno` files
- From the above folder run: `lcov –c –d . –o mainAppCovrage.info`
-- Then generate the HTML report: `genhtml mainAppCovrage.info` (the artifact will be located at the same folder named `index.html`)