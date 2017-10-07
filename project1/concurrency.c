#include <x86intrin.h>

/*
 * Concurrency 1: The Producer-Consumer Problem
 *
 * Group 37: Taylor Alexander Brown & Lucien Armand Tamdja Tamno
 * Oregon State University
 * CS 444: Operating Systems II
 * Fall 2017
 */

int random_wait();

/* an item is a structure with a number and a time */
struct item {
    int number, time;
};

/* a buffer is an array of 32 items */
struct item buffer[32];

/* entry point */
int main(int argc, char **argv)
{
}

/* generate a random wait number between 2 and 9 */
int random_wait() {
    return 2; /* FIXME */
}
