# myHttpServer
C++ based multi threaded slim HTTP server

# Initial development environment requierments
- `git` should be installed
- `cmake` should be installed
- Currently Ubuntu18.04 is a legitimate Linux distro that can be used as a development environment. 
- install GTEST: 
* `sudo apt-get install libgtest-dev`
* `cd /usr/src/gtest`
-- `sudo cmake CMakeLists.txt`
-- `sudo make`
-- `sudo cp lib/*.a /usr/lib`

# Build instructions:
- `cd build` (mkdir `build` if not present in the root folder of this repo).
- `build$ cmake ../`
- From within the `build` folder run the `make` command. It will build according to the Makefile that is present there (main artifcat is `myHttpServer.out`)

# Run unit tests:
- After sucessfully building the project, the unit tests (GTest based) will be built as well.
- To run ALL the unit tests: `build$ src/tests/unitTestsExe.out`
