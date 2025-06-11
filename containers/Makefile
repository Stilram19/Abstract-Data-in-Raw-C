# Compiler & flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iheader

# Project structure
SRC_DIR = src
HDR_DIR = header
BUILD_DIR = build
UNIT_TEST_DIR = test/unit_test
STRESS_TEST_DIR = test/stress_test

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Automatically detect unit and stress test source files
UNIT_TESTS = $(basename $(notdir $(wildcard $(UNIT_TEST_DIR)/*.c)))
STRESS_TESTS = $(basename $(notdir $(wildcard $(STRESS_TEST_DIR)/*.c)))

# Binaries
UNIT_TEST_BINS = $(addprefix $(BUILD_DIR)/unit_test_, $(UNIT_TESTS))
STRESS_TEST_BINS = $(addprefix $(BUILD_DIR)/stress_test_, $(STRESS_TESTS))

# Default target
all: test

test: $(UNIT_TEST_BINS) $(STRESS_TEST_BINS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for unit test binaries
$(BUILD_DIR)/unit_test_%: $(UNIT_TEST_DIR)/%.c $(SRC_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Rule for stress test binaries
$(BUILD_DIR)/stress_test_%: $(STRESS_TEST_DIR)/%.c $(SRC_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Run all unit test binaries
run-unit: $(UNIT_TEST_BINS)
	@for bin in $(UNIT_TEST_BINS); do \
		echo "Running $$bin..."; \
		./$$bin || exit 1; \
	done

# Run all stress test binaries
run-stress: $(STRESS_TEST_BINS)
	@for bin in $(STRESS_TEST_BINS); do \
		echo "Running $$bin..."; \
		./$$bin || exit 1; \
	done

clean:
	rm -rf $(BUILD_DIR)

