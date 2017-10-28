/*
 * Concurrency 2: The Dining Philosophers Problem
 *
 * File: concurrency2.c
 * 
 * Group 37: Taylor Alexander Brown & Lucien Armand Tamdja Tamno
 * Oregon State University
 * CS 444: Operating Systems II
 * Fall 2017
 */

#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdlib.h>

/* infinite loop */
#define loop while(1)

/* boolean type */
typedef enum {
    false,
    true
} bool;

/* philosopher threads */
pthread_t philosopher[5];

/* philosophers */
char *lao_tzu    = "Lao Tzu",
     *chuang_tzu  = "Chuang Tzu",
     *confucius   = "Confucius",
     *bodhidharma = "Bodhidharma",
     *sun_tzu     = "Sun Tzu";

/* chopstick i is between philosophers i-1 and i */
pthread_mutex_t chopstick[5] = {PTHREAD_MUTEX_INITIALIZER,
                                PTHREAD_MUTEX_INITIALIZER,
                                PTHREAD_MUTEX_INITIALIZER,
                                PTHREAD_MUTEX_INITIALIZER,
                                PTHREAD_MUTEX_INITIALIZER}

/* random seed */
int seedp;

/* random number between x and y inclusive */
int rand_between(int x, int y)
{
    return ((unsigned int)rand_r(&seedp) % (y-x+1)) + x;
}

/* philosopher thinking routine */
void think(char *name)
{
    int wait_time = rand_between(2,9);
    printf("%s is thinking for %d seconds\n", name, wait_time);
    sleep(wait_time);
}

/**/
void get_chopsticks();

/**/
void put_chopsticks();

/* philosopher eating routine */
void eat()
{
    int wait_time = rand_between(2,9);
    printf("%s is eating for %d seconds\n", name, wait_time);
    sleep(rand_between(1,20);
}

/* philosopher loop */
void *dine(void *name)
{
    loop {
        think(name);
        get_chopsticks();
        eat(name);
        put_chopsticks();
    }
}

/* create philosopher thread with index and name */
void create_philosopher(int i, char *name)
{
    status = pthread_create(&(philosopher[i]), NULL, dine, name);
    if (status != 0)
        exit(status);
}

/* main thread entry point */
int main(int argc, char **argv)
{
    /* set random seed */
    seedp = time(NULL);

    /* create philosophers */
    create_philosopher(0, lao_tzu);
    create_philosopher(1, chuang_tzu);
    create_philosopher(2, confucius);
    create_philosopher(3, bodhidharma);
    create_philosopher(4, sun_tzu);

    /* exit main process while threads still running */
    pthread_exit(NULL);
}
