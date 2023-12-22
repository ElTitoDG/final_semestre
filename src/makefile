#
#
#
#
# Makefile para codigo de C
# Autor: Julián Hinojosa Gil
# Autor Original: Gustavo Pantuza Coelho Pinto
# Since: 24.03.2016
# Archivo creado a partir de la plantilla proporcionada por
# el autor original y usada anteriormente en un proyecto
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
		LDFLAGS += -framework OpenGL -framework Cocoa -lm
	else ifeq ($(UNAME_S),Linux)
		LDFLAGS += -s -lGLU -lGL -lX11 -lm
	endif

endif

#
# COMPILATION RULES
#

.PHONY: dirs

default: help

# Help message
help:
	@echo "$(BLUE)Projecto Final Semestre$(END_COLOR)"
	@echo "$(BROWN)Bongo Game$(END_COLOR)"
	@echo
	@echo "Target rules:"
	@echo "    all      - Configura y compila el projecto"
	@echo "    cc    	- Compila y genera el archivo binario"
	@echo "    run      - Ejecuta el binario generado"
	@echo "    dirs     - Crea todos los directorios necesarios"
	@echo "    clean    - Depura los archivos generados"
	@echo "    help     - Imprime en pantalla el mensaje de ayuda"
	@echo
	

all: dirs cc

cc : *.$(SRCEXT)
	$(CC) $^ -Os -o ../$(BINDIR)/$(BINARY) $(CFLAGS) $(LDFLAGS)
	@echo "\nBinary file placed at" \
		"$(BROWN)$(BINDIR)/$(BINARY)$(END_COLOR)\n";



# Run the binary files
run: ../$(BINDIR)/$(BINARY)
	./$^

# Rule for creating the required dirs
dirs:
	mkdir -p ../$(SRCDIR) ../$(BINDIR)


# Rule for cleaning the project
clean:
	@rm -rvf ../$(BINDIR)/* 
