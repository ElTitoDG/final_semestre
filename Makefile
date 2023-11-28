#
#
#
#
# Makefile for C code
#
#
#
#

PROJECT_NAME := project
BINARY := game

OS := $(shell uname -s)

COLOR_PREFIX := e

ifeq ($(OS), Darwin)
	COLOR_PREFIX := 033
endif

# Color definition
BROWN =\$(COLOR_PREFIX)[0;33m
BLUE =\$(COLOR_PREFIX)[1;34m
END_COLOR =\$(COLOR_PREFIX)[0m

# Source code directory
BINDIR := bin
SRCDIR := src
LOGDIR := log
LIBDIR := lib

# Source code file extension
SRCEXT := c

# Defines the C compiler
ifeq ($(OS), Darwin)
	CC := clang
else
	CC := gcc
endif

# Defines language standards
STD := -std=c2x

# Specifies to CC the required warnings
#WARNS := -Wall -Wextra

# Flags for compiling
CFLAGS += -I../..


ifeq ($(OS),Windows_NT)
	LDFLAGS += -s -lopengl32 -lgdi32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LDFLAGS += -framework OpenGL -framework Cocoa
	else ifeq ($(UNAME_S),Linux)
		LDFLAGS += -s -lGLU -lGL -lX1
	endif
endif


# Debug options
DEBUG := -g3 -DDEBUG=1


#
# COMPILATION RULES
#

.PHONY: dirs

default: help

# Help message
help:
	@echo "$(BLUE)Projecto Final Semestre$(END_COLOR)"
	@echo
	@echo "Target rules:"
	@echo "    all      - Compiles and generates binary file"
	@echo "    run      - Run the current binary file"
	@echo "    dirs     - Creates all the required dirs"
#	@echo "    tests    - Compiles with cmocka and run tests binary file"
	@echo "    clean    - Clean the project by removing binaries"
	@echo "    help     - Prints a help message with target rules"
	@echo
	

all: src/main.c src/tigr.c
	clang $^ -Os -o bin/game $(CFLAGS) $(LDFLAGS)


# Run the binary files
run: $(BINDIR)/$(BINARY)
	./$^

# Rule for creating the required dirs
dirs:
	mkdir -p $(SRCDIR) $(BINDIR) $(LOGDIR) $(LIBDIR)


# Rule for cleaning the project
clean:
	@rm -rvf $(BINDIR)/* $(LIBDIR)/* *.txt; #$(LOGDIR)/*
