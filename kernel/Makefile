DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

CFLAGS?=
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -fno-stack-protector -std=gnu11
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude -I../libc/include/ -I ../libvector/include
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lvector -lk -lgcc

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel/disk_manager.o \
kernel/fs/fat32/fat_utf16_utf8.o \
kernel/fs/fat32/lfn.o \
kernel/fs/fat32/fat32.o \
kernel/fs/fat32/fat32_to_vfs.o \
kernel/vfs.o \
kernel/kheap.o \
kernel/time.o \
kernel/kernel.o \
kernel/font.o \

OBJS=\
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

LINK_LIST=\
$(LDFLAGS) \
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(LIBS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S 

all: Veonter.kernel

Veonter.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	# TODO: Detect ARM or X86 to disable grub-file on ARM platforms
	#grub-file --is-x86-multiboot Veonter.kernel || grub2-file --is-x86-multiboot Veonter.kernel

kernel/font.o: kernel/font.psf
	cd kernel && $(OBJCOPY) -I binary -O $(OBJCOPY_OUT_FMT) -B $(OBJCOPY_ARCH) font.psf font.o

$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f Veonter.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: Veonter.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp Veonter.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
