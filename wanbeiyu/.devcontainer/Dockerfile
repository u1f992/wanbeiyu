FROM ubuntu:24.04

RUN apt-get update && apt-get --yes --no-install-recommends install \
        clang-format \
        cmake \
        g++ \
        gcc \
        gdb \
        make \
    && rm -rf /var/lib/apt/lists/*
