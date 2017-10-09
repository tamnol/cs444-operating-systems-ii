/*
 * Concurrency 1: The Producer-Consumer Problem
 *
 * File: concurrency.h
 *
 * Group 37: Taylor Alexander Brown & Lucien Armand Tamdja Tamno
 * Oregon State University
 * CS 444: Operating Systems II
 * Fall 2017
 */

/* boolean type */
typedef enum {
    false,
    true
} bool;

/* an item is a structure with a number and a time */
struct item {
    int number, time;
};

/* return true if hardware supports rdrand */
extern bool supports_rdrand();

/* return an rdrand random number */
extern int rdrand();

/* initialize the mersenne twister pseudorandom number generator */
void mtrand_init();

/* return a mersenne twister pseudorandom number  */
int mtrand();

/* return a random integer between x and y, inclusive */
int rand_between(int x, int y);

/* thread constants */
#define NUMBER_OF_ITEMS 32
#define PRODUCER_THREADS 5
#define CONSUMER_THREADS 5
