FROM mcr.microsoft.com/devcontainers/cpp:dev-ubuntu24.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        cmake           \
        gcc-14          \
        g++-14          \
        gdb             \
        clangd          \
        liburing-dev    \
        pkg-config      \
        netcat-openbsd  \
        clang-format    \
        clang-tidy      \
        iwyu            \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 200 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-14 200 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*