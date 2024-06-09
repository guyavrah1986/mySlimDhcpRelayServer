# Use Ubuntu 22.04 as the base image
FROM ubuntu:22.04

LABEL Description="Build environment"

SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    cmake \
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

# Build the GTest framework
RUN cd /usr/src/gtest && cmake CMakeLists.txt && make && cp lib/*.a /usr/lib