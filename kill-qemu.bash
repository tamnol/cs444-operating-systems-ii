#!/bin/bash
#
# Group 37: Taylor Alexander Brown & Lucien Armand Tamdja Tamno
#
# Oregon State University
# CS 444: Operating Systems II
# Fall 2017
#
# Kill all QEMU processes begin run by the current user.
#
# Usage: ./kill-qemu.bash

killall --user `whoami` qemu-system-i386
