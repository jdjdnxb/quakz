CC := x86_64-elf-gcc

CFLAGS := -ffreestanding -g -O0 -Wall -Wextra -mcmodel=kernel \
	-Iinclude -Ilimine \
	-mno-sse -mno-sse2 -mno-mmx -msoft-float \
	-fno-builtin \

LDFLAGS := -T linker.ld -nostdlib

SRC := $(shell find src boot -name "*.c")
OBJ := $(SRC:.c=.o)

KERNEL := kernel.elf
ISO := quakz.iso
SPLASH := splash.jpg

all: $(KERNEL)

$(KERNEL): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

iso: $(KERNEL)
	rm -rf iso_root
	mkdir -p iso_root/boot

	cp $(KERNEL) iso_root/boot/kernel.elf
	cp $(SPLASH) iso_root/boot/splash.jpg
	cp limine.conf iso_root/
	cp limine/limine-bios-cd.bin iso_root/
	cp limine/limine-bios.sys iso_root/

	xorriso -as mkisofs \
		-b limine-bios-cd.bin \
		-no-emul-boot \
		-boot-load-size 4 \
		-boot-info-table \
		-o $(ISO) \
		iso_root

	./limine/limine.exe bios-install $(ISO)

run: iso
	qemu-system-x86_64 \
		-m 512M \
		-cdrom $(ISO) \
		-serial stdio

debug: clean iso
	qemu-system-x86_64 \
		-m 512M \
		-cdrom $(ISO) \
		-S -s \
		-no-reboot

clean:
	rm -f $(OBJ)
	rm -f $(KERNEL)
	rm -f $(ISO)
	rm -rf iso_root

.PHONY: all iso run debug clean