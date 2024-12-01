# slimDhcpRelayServer
C++20 based multi threaded slim DHCP relay (proxy) server

# Environment characteristics:
- Development machine: `Ubuntu 22.04`
- Compiler: `gcc/g++14`
- Build tool: `CMake 3.28`
- Source control: `git`
- Main language: `C++ 20`
- Architecture: `X86_64`
- Unit test framework: `GTest`

# Build development environment Docker image:
- OPTIONAL (if needed): Edit the `Dockerfile` in the root folder of the project as you wish 
- From the folder where the Dockerfile reside, run:`sudo docker build -t <image_name>:<version> .` for example: `docker build -t dev_env_image:0.1 .`
- You can run `docker images` to see all avialble images on this machine.
- To run the dev_env_image Docker image run with the source of the project mounted on it: `docker run -it --mount src="$(pwd)",target=/project,type=bind dev_env_image:0.1` 

# Initial development environment requierments:
- `sudo apt-get install git cmake build-essential libapr1-dev gzip zip net-tools`
- Install GTest:
- `sudo apt-get install libgtest-dev`
- `cd /usr/src/gtest`
- `sudo cmake CMakeLists.txt && sudo make && sudo cp lib/*.a /usr/lib`
- Install `google-perftools` and `libgoogle-perftools-dev`
- `sudo apt-get install google-perftools libgoogle-perftools-dev`
- The libgoogle-perftools-dev is for the gperftools/heap-checker.h.
- Install `lcov`: `sudo apt-get update install lcov` (version used: 1.14)
- Install log4cxx:
- `sudo apt-get install libapr1-dev libaprutil-dev liblog4cxx-dev`
- NOTE: For production environment, the following is needed: `liblog4cxx`, `libapr1` and `libaprutil`.

# Build instructions:
- `cd myslimDhcpRelayServer` (root folder of the project)
- Create the "out of source" `build` folder: `mkdir build`
- `cd build`
- `build$ cmake ../` for production code, OR
- `build$ cmake ../ -DBUILD_UNIT_TESTS=True` (for debug/unit test/ non production mode)
- `build$ make` (it will build according to the Makefile that is present there - main artifcat is `slimDhcpRelayServer.out`)

# Run unit tests:
- After sucessfully building the project, the unit tests (GTest based) will be built as well.
- To run ALL the unit tests: `build$ src/tests/unitTestsExe.out <full_path_to_logger_configuration_file>`
- Run a specific unit test: `build$ src/tests/unitTestsExe.out <full_path_to_logger_configuration_file> --gtest_filter=sampleObjectTest.createSingleMySampleObject`
- Run unit test with tcmalloc's heap leak detection enabled: 
- `build$ env HEAPCHECK=local src/tests/unitTestsExe.out <full_path_to_logger_configuration_file> --gtest_filter=sampleObjectTest.createSingleMySampleObject`

# Run playground function (for exploring/testing purposes):
- The project needs to be sucessfully built with the `-DBUILD_UNIT_TESTS=True`  (same as for building unit tests).
- Run the following (from the `build` folder): `./src/slimDhcpRelayServer.out <full_path_to_logger_configuration_file> -p <name_of_function_to_run`, for example: 
- `./src/slimDhcpRelayServer.out ../appLogging.properties -p setThreadCpuAffinityExample` (to run the `setThreadCpuAffinityExample` playground function).

# Generating unit test covrage: 
- Run the unit tests (as described above)
- From the `build` folder run: `lcov –c –d . –o testsCovrage.info`
- Then generate the HTML report: `genhtml testsCovrage.info`
- Several files will be added to current folder, out of which the `index.html` file will have the unit tests covrage report

# Application covarage:
- Build the application (according to the build instructions mentioned above)
- Run the application: `cd slimDhcpRelayServer/build/ && .src/myHttpServer <full_path_to_logger_configuration_file>` 
- Go to the `slimDhcpRelayServer/build/src/CMakeFiles/slimDhcpRelayServer.out.dir` there you will find the `main.cpp.gcda` and `main.cpp.gcno` files
- From the above folder run: `lcov –c –d . –o mainAppCovrage.info`
- Then generate the HTML report: `genhtml mainAppCovrage.info` (the artifact will be located at the same folder named `index.html`)
