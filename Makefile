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
CFLAGS := -O3 $(STD) $(WARNS)

# Debug options
DEBUG := -g3 -DDEBUG=1

# Libs dependency
ifeq ($(OS), Darwin)
	LIBS := -framework OpenGL -framework Cocoa -lm
else
	LIBS := -lGLU -lGL -lX11
endif

# %.o file names
NAMES := $(notdir $(basename $(wildcard $(SRCDIR)/*.$(SRCEXT))))
OBJECTS :=$(patsubst %,$(LIBDIR)/%.o,$(NAMES))


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

# Rule for link and generate the binary file
all: $(OBJECTS)
# @echo -en "$(BROWN)LD$(END_COLOR)";
	$(CC) -o $(BINDIR)/$(BINARY) $+ $(CFLAGS) $(LIBS)
	@echo "\nBinary file placed at" \
			  "$(BROWN)$(BINDIR)/$(BINARY)$(END_COLOR)\n";


# Rule for object bineries
$(LIBDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
# @echo -en "$(BROWN)CC$(END_COLOR)"
	$(CC) -c $^ -o $@ $(CFLAGS) 

# Run the binary files
run: $(BINDIR)/$(BINARY)
	./$^

# Rule for creating the required dirs
dirs:
	mkdir -p $(SRCDIR) $(BINDIR) $(LOGDIR) $(LIBDIR)


# Rule for cleaning the project
clean:
	@rm -rvf $(BINDIR)/* $(LIBDIR)/* *.txt; #$(LOGDIR)/*
