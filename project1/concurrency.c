/*
 * Concurrency 1: The Producer-Consumer Problem
 *
 * File: concurrency.c
 *
 * Group 37: Taylor Alexander Brown & Lucien Armand Tamdja Tamno
 * Oregon State University
 * CS 444: Operating Systems II
 * Fall 2017
 */

#include <stdio.h>
#include "concurrency.h"

struct item buffer[32];

int main(int argc, char **argv)
{
    return rand_between(2,9);
}

void mtrand_init()
{
    int seed = time(NULL);
    init_genrand(seed);
}

int mtrand()
{
    return genrand_int32();
}

int rand_between(int x, int y)
{
    unsigned int n;

    if ((supports_rdrand() == false) || ((n=rdrand()) == 0))
        n = mtrand();

    return (n % (y-x+1)) + x;
}
