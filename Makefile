#
# Makefile
#
# NOTE(sdsmith): made to be run in root of project directory.

### Config 
CC=gcc
CCARCH=-m32
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
CLFLAGS=-nostdlib -lgcc

ASMC=nasm
ASMCARCH=elf32


BUILD_DIR=./build
OBJ_DIR=./build/obj
SRC_DIR=./src



_DEPS =

_OBJS = \
	main.o \
	boot.o \
	video.o \
	util/string.o \
	util/stdio.o



### Build prep
DEPS = $(patsubst %,$(SRC_DIR)/%,$(_DEPS))
OBJS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))



### Build
all: directories kernal.bin


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



.PHONY: clean directories

directories:
	if [ ! -d "$(BUILD_DIR)" ]; then mkdir $(BUILD_DIR); fi
	if [ ! -d "$(OBJ_DIR)" ]; then mkdir $(OBJ_DIR); fi
	if [ ! -d "$(SRC_DIR)" ]; then mkdir $(SRC_DIR); fi


clean:
	rm -f $(OBJ_DIR)/*.o
