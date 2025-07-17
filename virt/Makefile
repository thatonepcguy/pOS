# Toolchain
CC := aarch64-none-elf-gcc

SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

SRC := $(shell find $(SRC_DIR) -type f \( -name '*.c' -o -name '*.S' \))

OBJS := $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/%, $(SRC:.c=.o))
OBJS := $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/%, $(OBJS:.S=.o))

ELF := $(BUILD_DIR)/kernel.elf
MAP := $(BUILD_DIR)/kernel.map

CFLAGS := -std=c11 -O2 -g3 -Wall -Wextra -fno-stack-protector -ffreestanding -nostdlib -I$(INCLUDE_DIR)
LDFLAGS := -Wl,-Tkernel.ld,-Map=$(MAP)

QEMU := qemu-system-aarch64
QEMU_MACHINE := -machine virt

.PHONY: all run clean

all: $(ELF)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

run: $(ELF)
	$(QEMU) $(QEMU_MACHINE) -kernel $(ELF) -cpu cortex-a72 -m 2048M

clean:
	rm -rf $(BUILD_DIR)
