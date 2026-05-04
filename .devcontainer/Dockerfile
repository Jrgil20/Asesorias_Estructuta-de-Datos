FROM mcr.microsoft.com/devcontainers/base:debian

# Instala compiladores y herramientas para C/C++
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    gdb \
    clang-format \
    git \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Si necesitas otras herramientas, agrégalas aquí.
