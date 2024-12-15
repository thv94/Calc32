CC = gcc
CSTD = c90
OPT_LEVEL = -O2

SRC_DIR = src
INC_DIR = include
OBJ_DIR = .o

CFLAGS = -Wall -Wextra -Werror -Wpedantic -I$(INC_DIR) -std=$(CSTD) $(OPT_LEVEL)
LFLAGS = -lgdi32 -mwindows

TARGET = calc

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

clean:
	rm -rf $(OBJ_FILES) $(TARGET)