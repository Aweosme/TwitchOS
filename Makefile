#
# Makefile
#
# NOTE(sdsmith): made to be run in root of project directory.

### Config
OSNAME = aweosme

CC = gcc
CCARCH = -m32
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
CLFLAGS = -nostdlib -lgcc
ASMC = nasm
ASMCARCH = elf32


BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj
SRC_DIR = ./src

ISO_DIR = $(BUILD_DIR)/iso
BOOT_DIR = $(ISO_DIR)/boot
GRUB_DIR = $(BOOT_DIR)/grub

.PHONY: clean setup_build_directory kernal setup_iso run

_DEPS =

_OBJS = \
	main.o \
	boot.o \
	terminal.o \
	descriptor_tables/gdt.o \
	descriptor_tables/gdt_flush.o \
	descriptor_tables/idt.o \
	descriptor_tables/idt_flush.o \
	util/string.o \
	util/stdio.o

define GRUB_CFG
menuentry "$(OSNAME)" {
	multiboot /boot/kernal.bin
}
endef

### Build prep
DEPS = $(patsubst %,$(SRC_DIR)/%,$(_DEPS))
OBJS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))

### Build
all: setup_iso

# any .o file from .c file created from the .c file and the list of dependants
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@mkdir -p $(dir $@)
	$(CC) $(CCARCH) -c -o $@ $< $(CFLAGS)

# any .o file from .asm file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(dir $@)
	$(ASMC) -f $(ASMCARCH) -o $@ $^

kernal.bin: $(OBJS)
	$(CC) $(CCARCH) -o $(BUILD_DIR)/$@ $^ $(CLFLAGS)

setup_build_directory:
	@if [ ! -d "$(BUILD_DIR)" ]; then mkdir $(BUILD_DIR); fi
	@if [ ! -d "$(OBJ_DIR)" ]; then mkdir $(OBJ_DIR); fi
	@if [ ! -d "$(SRC_DIR)" ]; then mkdir $(SRC_DIR); fi

kernal: setup_build_directory kernal.bin

export GRUB_CFG
setup_iso: setup_build_directory kernal.bin
	@if [ ! -d "$(ISO_DIR)" ]; then mkdir $(ISO_DIR); fi
	@if [ ! -d "$(BOOT_DIR)" ]; then mkdir $(BOOT_DIR); fi
	@if [ ! -d "$(GRUB_DIR)" ]; then mkdir $(GRUB_DIR); fi

	cp $(BUILD_DIR)/kernal.bin $(BOOT_DIR)
	@if [ ! -f "$(GRUB_DIR)/grub.cfg" ]; then \
		echo "$$GRUB_CFG" > $(GRUB_DIR)/grub.cfg; \
	fi
	grub-mkrescue -o $(ISO_DIR)/$(OSNAME).iso $(ISO_DIR)

clean:
	@rm -f $(OBJ_DIR)/*.o
	@rm -f $(BUILD_DIR)/*.bin
	@rm -rf $(ISO_DIR)
	@rm -rf $(BUILD_DIR)
	@rm -rf $(OBJ_DIR)

run: setup_iso
	@qemu-system-i386 -m 256M -cdrom $(ISO_DIR)/$(OSNAME).iso -k en-us
