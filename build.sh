#!/bin/bash

set -e

echo "Getting bootloader..."
if [ ! -d "limine" ]; then
    git clone https://github.com/limine-bootloader/limine.git --branch=v8.x-binary --depth=1
fi
make -C limine

echo "Building kernel..."
echo "#define COMMIT \"$(git rev-parse --short HEAD)\"" > kernel/include/version.h
make -C kernel

echo "Setting up disk image..."
mkdir -p sysroot
mkdir -p sysroot/boot
cp -v bin/pangolin sysroot/boot/

echo "Setting up initial ramdisk archive..."
tar --create --file=sysroot/boot/initrd --format=ustar -C initrd home

echo "Setting up bootloader..."
mkdir -p sysroot/boot/limine
cp -v limine.conf limine/limine-bios.sys limine/limine-bios-cd.bin \
      limine/limine-uefi-cd.bin sysroot/boot/limine/

mkdir -p sysroot/EFI/BOOT
cp -v limine/BOOTX64.EFI sysroot/EFI/BOOT/
cp -v limine/BOOTIA32.EFI sysroot/EFI/BOOT/

echo "Creating disk image..."
xorriso -as mkisofs -b boot/limine/limine-bios-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        --efi-boot boot/limine/limine-uefi-cd.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        sysroot -o pangolin.iso

echo "Installing bootloader"
./limine/limine bios-install pangolin.iso

qemu-system-x86_64 pangolin.iso -serial stdio --no-reboot --no-shutdown

