# Concurrency 1: The Producer-Consumer Problem
#
# Makefile
#
# Group 37: Taylor Alexander Brown & Lucien Armand Tamdja Tamno
# Oregon State University
# CS 444: Operating Systems II
# Fall 2017

CC = gcc
CFLAGS =

all: concurrency test

concurrency: mt19937ar.o concurrency.S concurrency.c
	$(CC) $(CFLAGS) mt19937ar.o concurrency.S concurrency.c -o concurrency

test: mt19937ar.o concurrency.S concurrency.c test.S test.c
	$(CC) $(CFLAGS) -c concurrency.c -o concurrency.o
	objcopy --redefine-sym main=concurrency_main concurrency.o
	$(CC) $(CFLAGS) mt19937ar.o concurrency.S concurrency.o test.S test.c -o test

mt19937ar.o: mt19937ar.c
	$(CC) $(CFLAGS) -c mt19937ar.c -o mt19937ar.o
	objcopy --redefine-sym main=mt19937ar_main mt19937ar.o
