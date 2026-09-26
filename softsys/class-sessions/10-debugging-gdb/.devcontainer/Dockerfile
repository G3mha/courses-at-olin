# Switch these two lines to force an x86 container. This gives ARM users a consistent environment,
# at the expense of being *very* (4-5x) slow.
#FROM mcr.microsoft.com/devcontainers/base:jammy as softsys
FROM --platform=x86-64 mcr.microsoft.com/devcontainers/base:jammy as softsys_x86

# This makes `man` work. It's very slow (~60s), so we put it at the beginning so Docker caches it.
RUN yes | unminimize

# Install dependencies
RUN sudo apt-get update && \
	sudo apt-get install -y \
		gcc \
		gdb \
		make \
		cmake \
		clang-format \
		clang-tidy \
		libcriterion-dev \
		valgrind \
		file

USER vscode
RUN bash -c "$(curl -fsSL https://gef.blah.cat/sh)"
