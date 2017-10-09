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

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "concurrency.h"

/* shared buffer */
struct item buffer[NUMBER_OF_ITEMS];

/* producer and consumer thread lists */
pthread_t producer[PRODUCER_THREADS];
pthread_t consumer[CONSUMER_THREADS];

/* function prototypes */
void initialize_buffer();
void create_threads(int number, pthread_t thread[], void *(*start)(void*));
void *producer_start(void *argument);
void *consumer_start(void *argument);

/* main thread entry point */
int main(int argc, char **argv)
{
    /* initialize mersenne twister */
    mtrand_init();

    /* initialize buffer */
    initialize_buffer();

    /* create producer threads */
    create_threads(PRODUCER_THREADS, producer, producer_start);

    /* create consumer threads */
    create_threads(CONSUMER_THREADS, consumer, consumer_start);

    printf("main process %d\n", getpid()); /* DEBUG */

    /* exit main process while threads still running */
    pthread_exit(NULL);
}

/* initialize buffer to zero */
void initialize_buffer()
{
    int i;

    for (i=0; i<NUMBER_OF_ITEMS; ++i) {
        buffer[i].number = 0;
        buffer[i].time = 0;
    }
}

/* create threads */
void create_threads(int number, pthread_t thread[], void *(*start)(void*))
{
    int i, status;

    for (i=0; i<number; ++i) {
        status = pthread_create(&(thread[i]), NULL, start, NULL);
        if (status != 0)
            exit(status);
    }
}

/* producer thread entry point */
void *producer_start(void *argument)
{
    printf("producer thread 0x%lx\n", (unsigned long)pthread_self()); /* DEBUG */
    pthread_exit(NULL);
}

/* consumer thread entry point */
void *consumer_start(void *argument)
{
    printf("consumer thread 0x%lx\n", (unsigned long)pthread_self()); /* DEBUG */
    pthread_exit(NULL);
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
