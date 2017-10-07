#!/bin/bash
#
# Linux Boot Script
#
# Group 37: Taylor Alexander Brown & Lucien Armand Tamdja Tamno
# Oregon State University
# CS 444: Operating Systems II
# Fall 2017
#
# Usage: ./boot.bash [/path/to/kernel.bin]

# source the environment configuration script
source /scratch/files/environment-setup-i586-poky-linux

# run kernel in qemu
qemu-system-i386 \
    -gdb tcp::5537 \
    -S \
    -nographic \
    -kernel $1 \
    -drive file=/scratch/fall2017/37/disks/core-image-lsb-sdk-qemux86.ext4,if=virtio \
    -enable-kvm \
    -net none \
    -usb \
    -localtime \
    --no-reboot \
    --append 'root=/dev/vda rw console=ttyS0 debug' \
    &

# boot kernel in gdb
$GDB --command=boot.gdb
