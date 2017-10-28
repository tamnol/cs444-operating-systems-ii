# Concurrency 2: The Dining Philosophers Problem
#
# File: Makefile
#
# Group 37: Taylor Alexander Brown & Lucien Armand Tamdja Tamno
# Oregon State University
# CS 444: Operating Systems II
# Fall 2017

CC = gcc
CFLAGS = -pthread -ggdb

all:
	$(CC) $(CFLAGS) concurrency2.c -o concurrency2

CS444_concurrency2_37.tar.bz2:
	tar cvfj CS444_concurrency2_37.tar.bz2 Makefile concurrency2.c

clean:
	rm -f concurrency2 CS444_concurrency2_37.tar.bz2
