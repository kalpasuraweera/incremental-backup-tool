# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Iinclude

# Folders
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Output executable name
TARGET = $(BIN_DIR)/app

# All .c files in src/
SRC = $(wildcard $(SRC_DIR)/*.c)

# Convert .c to .o, send to obj/
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Default rule
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o $(TARGET)

# Compile .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: all
	./$(TARGET)

# Remove compiled files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Rebuild everything from scratch
rebuild: clean all

.PHONY: all run clean rebuild

