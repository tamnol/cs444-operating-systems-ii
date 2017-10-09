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

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "concurrency.h"

/* shared buffer */
struct item buffer[NUMBER_OF_ITEMS];
pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER;

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

    #ifdef DEBUG
    printf("main process %d\n", getpid());
    #endif

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

/* return true if item is empty, otherwise return false */
bool item_is_empty(struct item *item)
{
    return ((item->number == 0) && (item->time == 0));
}

/* producer thread entry point */
void *producer_start(void *argument)
{
    int i, wait_time;
    struct item *item = NULL;
    unsigned long tid = (unsigned long)pthread_self();

    /* print thread creation */
    printf("0x%lx: producer thread created\n", tid);

    loop {

        /* lock the buffer */
        pthread_mutex_lock(&buffer_lock); /* TODO error check */

        /* find the address of the first empty item */
        for (i=0; i<NUMBER_OF_ITEMS; ++i) {
            if (item_is_empty(&buffer[i])) {
                item = &buffer[i];
                break;
            }
        }

        /* if an empty item was found */
        if (item != NULL) {

            /* wait for item to be produced */
            sleep(wait_time=rand_between(3,7));

            /* produce new item */
            item->number = rand();
            item->time = rand_between(2,9);

            /* print item produced */
            printf("0x%lx: produced %d after %d seconds\n",
                   tid, item->number, wait_time);

            /* reset item address */
            item = NULL;
        }

        /* unlock the buffer and continue */
        pthread_mutex_unlock(&buffer_lock); /* TODO error check */
    }
}

/* consumer thread entry point */
void *consumer_start(void *argument)
{
    int i;
    struct item *item = NULL;
    unsigned long tid = (unsigned long)pthread_self();

    /* print thread creation */
    printf("0x%lx: consumer thread created\n", tid);

    loop {

        /* lock the buffer */
        pthread_mutex_lock(&buffer_lock); /* TODO error check */

        /* find the address of the first full item */
        for (i=0; i<NUMBER_OF_ITEMS; ++i) {
            if (!item_is_empty(&buffer[i])) {
                item = &buffer[i];
                break;
            }
        }

        /* if a full item was found */
        if (item != NULL) {

            /* wait for item to be consumed */
            sleep(item->time);

            /* print item consumed */
            printf("0x%lx: consumed %d after %d seconds\n",
                   tid, item->number, item->time);

            /* make item empty */
            item->time = 0;
            item->number = 0;

            /* reset item address */
            item = NULL;
        }

        /* unlock the buffer */
        pthread_mutex_unlock(&buffer_lock); /* TODO error check */
    }
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

int rand()
{
    int n;

    if ((supports_rdrand() == false) || ((n=rdrand()) == 0))
        n = mtrand();

    return n;
}

int rand_between(int x, int y)
{
    return ((unsigned int)rand() % (y-x+1)) + x;
}
