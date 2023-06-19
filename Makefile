# OBJS are the target source files to compile
OBJS = main.c student_generation.c queue.c name_generator.c

# Compiler
CC = gcc

# Linker flags
LINKER_FLAGS = -lm

# OBJ_NAME of executable
OBJ_NAME = dojo

# build target
all: $(OBJS)
	$(CC) -o $(OBJ_NAME) $(OBJS) $(LINKER_FLAGS)

clean:
	rm $(OBJ_NAME)
