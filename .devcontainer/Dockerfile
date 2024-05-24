FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
    ca-certificates \
    build-essential \
    cmake \
    gdb \
    git \
    curl \
    wget \
    valgrind \
    libreadline-dev \
    && rm -rf /var/lib/apt/lists/*
