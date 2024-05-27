FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
    cmake \
    curl \
    gdb \
    git \
    gnupg \
    libreadline-dev \
    openssh-client \
    sudo \
    valgrind \
    wget \
    && rm -rf /var/lib/apt/lists/* \
