# Use Ubuntu 22.04 as the base image
FROM ubuntu:22.04

LABEL Description="Build environment"

SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    wget \
    gzip \
    zip \
    net-tools \
    google-perftools \
    libgoogle-perftools-dev \
    lcov \
    libapr1-dev \
    liblog4cxx-dev \
    libgtest-dev \
    google-perftools \
    libgoogle-perftools-dev

RUN wget --no-check-certificate https://github.com/Kitware/CMake/releases/download/v3.30.0/cmake-3.30.0-linux-x86_64.sh && \
    chmod +x cmake-3.30.0-linux-x86_64.sh && \
    ./cmake-3.30.0-linux-x86_64.sh --skip-license --prefix=/usr/local && \
    rm cmake-3.30.0-linux-x86_64.sh

# Check cmake version 
RUN cmake --version

# Build the GTest framework
RUN cd /usr/src/gtest && cmake CMakeLists.txt && make && cp lib/*.a /usr/lib

# Copy the project sources into the container image
RUN mkdir $HOME/project
COPY . $HOME/project/
RUN ls -l $HOME/project/

# TODO: build the project
# cd .. && rm -rf build && mkdir build && cd build && cmake ../ -DBUILD_UNIT_TESTS=True  && make