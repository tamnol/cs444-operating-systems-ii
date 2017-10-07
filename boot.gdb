# Debugger Script to Connect GDB to QEMU
#
# Group 37: Taylor Alexander Brown & Lucien Armand Tamdja Tamno
# Oregon State University
# CS 444: Operating Systems II
# Fall 2017
#
# Usage: (gdb) source debug.gdb

# connect to QEMU
target remote :5537

# boot linux
continue
