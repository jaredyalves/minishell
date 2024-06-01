FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y --no-install-recommends curl libfreetype6 libxext6 libxi6 libxrender1 libxtst6 procps unzip \
    && apt-get install -y --no-install-recommends build-essential cmake gdb git openssh-client valgrind \
    && apt-get install -y --no-install-recommends libreadline-dev \
    && rm -rf /var/lib/apt/lists/*
