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

CFLAGS += $(STD) -I../..

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

demo : $(SRCDIR)/*.$(SRCEXT)
	clang $^ -Os -o ../$(BINDIR)/$(BINARY) $(CFLAGS) $(LDFLAGS)
