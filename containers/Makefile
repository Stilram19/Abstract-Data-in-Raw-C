CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iheader
SRC_DIR = src
HDR_DIR = header
BUILD_DIR = build
UNIT_TEST_DIR = test/unit_test
STRESS_TEST_DIR = test/stress_test

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

UNIT_TEST_SRC = $(UNIT_TEST_DIR)/dynamic_array.c
UNIT_TEST_BIN = $(BUILD_DIR)/unit_test_dynamic_array

STRESS_TEST_SRC = $(STRESS_TEST_DIR)/dynamic_array.c
STRESS_TEST_BIN = $(BUILD_DIR)/stress_test_dynamic_array

all: test

test: $(UNIT_TEST_BIN) $(STRESS_TEST_BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link unit test binary
$(UNIT_TEST_BIN): $(UNIT_TEST_SRC) $(SRC_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Link stress test binary
$(STRESS_TEST_BIN): $(STRESS_TEST_SRC) $(SRC_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

run-unit: $(UNIT_TEST_BIN)
	./$(UNIT_TEST_BIN)

run-stress: $(STRESS_TEST_BIN)
	./$(STRESS_TEST_BIN)

clean:
	rm -rf $(BUILD_DIR)

