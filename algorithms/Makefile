# --- Variables ---
CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -Iheader
SRC_DIR     := src
TEST_DIR    := test
OBJ_DIR     := obj
BIN_DIR     := bin

SRCS        := $(wildcard $(SRC_DIR)/*.c)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST_SRCS   := $(wildcard $(TEST_DIR)/*.c)
TEST_BINS   := $(TEST_SRCS:$(TEST_DIR)/%.c=$(BIN_DIR)/%)

# --- Rules ---

# default rule: build all tests
all: $(TEST_BINS)

# this links the specific test object with all general project objects
$(BIN_DIR)/%: $(TEST_DIR)/%.c $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@

# rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# create directories if they don't exist
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run tests
test: all
	@echo "Running tests..."
	@for test in $(TEST_BINS); do ./$$test; done

.PHONY: all clean test
