#
# libogl64/Makefile: Makefile for libogl64.
#
# n64chain: A (free) open-source N64 development toolchain.
# Copyright 2014-16 Tyler J. Stachecki <stachecki.tyler@gmail.com>
#
# This file is subject to the terms and conditions defined in
# 'LICENSE', which is part of this source code package.
#

ifdef SystemRoot
FIXPATH = $(subst /,\,$1)
RM = del /Q
CP = copy
else
FIXPATH = $1
RM = rm -f
CP = cp
endif

AS = $(call FIXPATH,$(CURDIR)/../tools/bin/mips64-elf-as)
AR = $(call FIXPATH,$(CURDIR)/../tools/bin/mips64-elf-gcc-ar)
CC = $(call FIXPATH,$(CURDIR)/../tools/bin/mips64-elf-gcc)
CPP = $(call FIXPATH,$(CURDIR)/../tools/bin/mips64-elf-cpp)
LD = $(call FIXPATH,$(CURDIR)/../tools/bin/mips64-elf-ld)
OC = $(call FIXPATH,$(CURDIR)/../tools/bin/mips64-elf-objcopy)

RSPASM = $(call FIXPATH,$(CURDIR)/../tools/bin/rspasm)

CFLAGS = -Wall -Wextra -pedantic -std=c99 \
	-I../include -I./include -save-temps
OPTFLAGS = -Os -march=vr4300 -mtune=vr4300 -mabi=eabi -mgp32 -mlong32 \
	-flto -ffat-lto-objects -ffunction-sections -fdata-sections \
	-G4 -mno-extern-sdata -mgpopt -mfix4300 -mbranch-likely \
	-mno-check-zero-division

ASMFILES = $(call FIXPATH,\
)

CFILES = $(call FIXPATH,\
	src/glut64.c \
)

UCODES = $(call FIXPATH,\
)

OBJFILES = \
	$(CFILES:.c=.o) \
	$(ASMFILES:.s=.o) \
	$(UCODES:.rsp=.o)

DEPFILES = $(OBJFILES:.o=.d)

#
# Primary targets.
#
libglut64.a: $(OBJFILES)
	@echo $(call FIXPATH,"Building: libglut64/$@")
	@$(AR) rcs $@ $^
	@$(CP) $(call FIXPATH, include/glut64.h) $(call FIXPATH, ../include)
	@$(CP) $(call FIXPATH, libglut64.a) $(call FIXPATH, ../lib)

#
# Generic compilation/assembly targets.
#
%.o: %.s
	@echo $(call FIXPATH,"Assembling: libglut64/$<")
	@$(CC) -x assembler-with-cpp $(CFLAGS) $(OPTFLAGS) -MMD -c $< -o $@

%.o: %.c 
	@echo $(call FIXPATH,"Compiling: libglut64/$<")
	@$(CC) $(CFLAGS) $(OPTFLAGS) -MMD -c $< -o $@

%.o: %.rsp %.rsps
	@echo $(call FIXPATH,"Assembling: $(ROM_NAME)/$@")
	@$(CPP) -E -Iucodes $< > $(<:.rsp=.rsppch)
	@$(RSPASM) $(<:.rsp=.rsppch) -o $(<:.rsp=.bin)
	@$(CC) -x assembler-with-cpp $(CFLAGS) $(OPTFLAGS) -MMD -c $(<:.rsp=.rsps) -o $@

#
# Clean project target.
#
.PHONY: clean
clean:
	@echo "Cleaning libglut64..."
	@$(RM) libglut64.a $(DEPFILES) $(OBJFILES)

