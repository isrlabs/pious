# Set up cross-compilation toolchain
TOOLCHAIN	= arm-eabi-none
CC		= $(TOOLCHAIN)-gcc
AS		= $(TOOLCHAIN)-as
LD		= $(TOOLCHAIN)-ld
OBJCOPY		= $(TOOLCHAIN)-objcopy

# Targets
BUILDDIR	= $(PWD)/../build
OBJDIR		= $(PWD)/../objs
INCLUDES	= $(PWD)/../include
TARGET		= kernel.img
AOUT		= kernel.elf

# Build options
CFLAGS		:= -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk
CLFAGS		+= -mtune=arm1176jzf-s -I$(INCLUDES)


all: 
	@echo "This Makefile is still in progress."

#.PHONY: all
#all: $(TARGET)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(TARGET): $(AOUT)
	   $(OBJCOPY) $(AOUT) -O binary $@

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.s
	$(AS) -o $@ $<
