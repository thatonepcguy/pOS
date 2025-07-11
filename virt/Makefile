# Toolchain
CC := aarch64-none-elf-gcc

SRC := boot.S main.c uart.c memory.c string.c kprintf.c trapHandlerC.c trapHandlerS.S vectors.S heap.c common.c
BUILD := build
OBJS := $(patsubst %.S,$(BUILD)/%.o,$(filter %.S,$(SRC))) \
        $(patsubst %.c,$(BUILD)/%.o,$(filter %.c,$(SRC)))


ELF := $(BUILD)/kernel.elf
MAP := $(BUILD)/kernel.map

CFLAGS := -std=c11 -O2 -g3 -Wall -Wextra -fno-stack-protector -ffreestanding -nostdlib -Iinclude
LDFLAGS := -Wl,-Tkernel.ld,-Map=$(MAP)

QEMU := qemu-system-aarch64
QEMU_MACHINE := -machine virt

.PHONY: all run clean

all: $(ELF)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: %.S | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

run: $(ELF)
	$(QEMU) $(QEMU_MACHINE) -kernel $(ELF) -cpu cortex-a72 -m 2048M

clean:
	rm -rf $(BUILD)
