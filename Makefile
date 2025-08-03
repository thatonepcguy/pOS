#    * raspix is a custom OS designed to function on the Raspberry Pi 4b.
#    * Copyright (C) 2025  Caleb A. Jacka
#    *  
#    * This program is free software: you can redistribute it and/or modify
#    * it under the terms of the GNU General Public License as published by
#    * the Free Software Foundation, either version 3 of the License, or
#    * (at your option) any later version.
#    * 
#    * This program is distributed in the hope that it will be useful,
#    * but WITHOUT ANY WARRANTY; without even the implied warranty of
#    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    * GNU General Public License for more details.
#    * 
#    * You should have received a copy of the GNU General Public License
#    * along with this program.  If not, see <https://www.gnu.org/licenses/>.
#    * 
#    * If contact with the original author is needed, he is available via email at 
#    * calebjacka@gmail.com

# Toolchain
CC := aarch64-none-elf-gcc
OBJCOPY := aarch64-linux-gnu-objcopy

SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

SRC := $(shell find src -type f \( -name "*.c" -o -name "*.S" \))
OBJS := $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/%, $(SRC:.c=.o))
OBJS := $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/%, $(OBJS:.S=.o))

ELF := $(BUILD_DIR)/kernel.elf
MAP := $(BUILD_DIR)/kernel.map

CFLAGS := -std=c11 -O2 -g3 -Wall -Wextra -fno-stack-protector -ffreestanding -nostdlib -I$(INCLUDE_DIR)
LDFLAGS := -Wl,-Tkernel.ld,-Map=$(MAP)

.PHONY: all clean

all: $(ELF)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(BUILD_DIR)
