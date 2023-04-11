PROJDIRS := src

CD := $(shell echo %cd%)
ASM_SRCFILES := $(shell dir /s /b $(PROJDIRS)"\*.asm")
CPP_SRCFILES := $(shell dir /s /b $(PROJDIRS)"\*.cpp")
C_SRCFILES := $(shell dir /s /b $(PROJDIRS)"\*.c")
HDRFILES := $(shell dir /s /b $(PROJDIRS)"\*.h")

CPP_OBJECT_FILES := $(foreach item,$(CPP_SRCFILES), build/$(notdir ${item}).o)
C_OBJECT_FILES := $(foreach item,$(C_SRCFILES), build/$(notdir ${item}).o)
ASM_OBJECT_FILES := $(foreach item,$(ASM_SRCFILES), build/$(notdir ${item}).o)

FLAGS=-m32 -ffreestanding -nostdlib -nostdinc -fpermissive -fno-exceptions -fno-rtti
CPP=g++
CC=gcc
ASFLAGS=-f elf32
NASM= nasm $(ASFLAGS)
OBJCOPY=objcopy

LDFLAGS=-T link.ld -m i386pe
 
all: build qemu
build: clean copy $(C_OBJECT_FILES) $(CPP_OBJECT_FILES) $(ASM_OBJECT_FILES) link objcopy

copy:
	mkdir build\src
	mkdir build\src\asm
	
	for /r %%f in (*.h) do copy %%f "build\src\%%~nxf"
	for /r %%f in (*.cpp) do copy %%f "build\src\%%~nxf"
	for /r %%f in (*.c) do copy %%f "build\src\%%~nxf"
	for /r %%f in (*.asm) do copy %%f "build\src\asm\%%~nxf"
	
clean: 
	del /q build\*
	for /d %%x in (build\*) do @rd /s /q "%%x"


link:
	ld $(LDFLAGS) -o build/kernel $(C_OBJECT_FILES) $(CPP_OBJECT_FILES) $(ASM_OBJECT_FILES)

qemu:
	qemu-system-i386 -kernel build/kernel.elf

compile_cpp:
	$(CPP) $(FLAGS) $(HDRFILES) $(CPP_SRCFILES) -o build/cpp.o

compile_asm:
	$(NASM) $(ASM_SRCFILES) -o build/asm.o 

build/%.c.o: build/src/%.c
	$(CC) $(FLAGS) -c $< -o $@

build/%.cpp.o: build/src/%.cpp
	$(CPP) $(FLAGS) -c $< -o $@

build/%.asm.o: build/src/asm/%.asm
	$(NASM) $< -o $@

list:
	@echo $(CPP_OBJECT_FILES)

objcopy:
	objcopy -O elf32-i386 build/kernel build/kernel.elf


