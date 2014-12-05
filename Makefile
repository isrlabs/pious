# Set up cross-compilation toolchain
TOOLCHAIN	 = arm-none-eabi
CC		 = $(TOOLCHAIN)-gcc
AS		 = $(TOOLCHAIN)-as
LD		 = $(TOOLCHAIN)-ld
OBJCOPY		 = $(TOOLCHAIN)-objcopy
OBJDUMP		 = $(TOOLCHAIN)-objdump

# Model should be 1 for the original Model A / Model B, and 2 for
# the A+/B+.
MODEL		?= 2

# Targets
BUILDDIR	 = build
OBJDIR		 = objs
INCLUDES	 = include
SRCDIR		 = src
TARGET		 = kernel.img
LINKER		 = pious.ld
AOUT		 = $(BUILDDIR)/kernel.elf

OBJS		 = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.c))

MAP		 = $(BUILDDIR)/kernel.map
LIST		 = $(BUILDDIR)/kernel.list
START		 = $(OBJDIR)/start.o

# Build options
CFLAGS		+= -O2 -mfpu=vfp -mfloat-abi=soft -march=armv6zk
CFLAGS		+= -mtune=arm1176jzf-s -I$(INCLUDES)
CFLAGS		+= -DMODEL=$(MODEL)


# all: 
# 	@echo "This Makefile is still in progress."
# 	@echo "Objects: $(OBJS)"
# 	@echo "Source directory: $(SRCDIR)"
# 	@echo "Sources: $(wildcard $(SRCDIR)/*.c)"
# 	@echo "a.out: $(AOUT)"

.PHONY: all
all: $(TARGET) $(LIST)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(TARGET): $(AOUT)
	$(OBJCOPY) $(AOUT) -O binary $@

$(AOUT): $(OBJS) $(LINKER) $(START)
	$(LD) -Map $(MAP) -o $@ -T $(LINKER) $(OBJS) $(START)

$(LIST): $(AOUT)
	$(OBJDUMP) -d $(AOUT) > $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.s $(OBJDIR)
	$(AS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(OBJDIR)/*.d
