/*
 * Concurrency 2: The Dining Philosophers Problem
 *
 * File: concurrency2.c
 * 
 * Group 37: Taylor Alexander Brown & Lucien Armand Tamdja Tamno
 * Oregon State University
 * CS 444: Operating Systems II
 * Fall 2017
 *
 * Algorithm adapted from:
 * https://www.cs.indiana.edu/classes/p415/hw/project/dining-philosophers/index.htm
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

/* philosopher names */
char *name[5] = {"Lao Tzu", "Chuang Tzu", "Confucius", "Bodhidharma", "Sun Tzu" };

/* philosopher states */
enum state {
    THINKING,
    EATING,
    HUNGRY
};

/* mutual exclusion lock */
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/* chopstick i is between philosophers i and i+1 */
sem_t chopstick[5];

/* philosopher state, initially THINKING */
enum state philosopher_state[5] = { THINKING, THINKING, THINKING, THINKING, THINKING };

/* random seed */
int seedp;

/* random number between x and y inclusive */
int rand_between(int x, int y)
{
    return ((unsigned int)rand_r(&seedp) % (y-x+1)) + x;
}

/* philosopher thinking routine */
void think(int i)
{
    int wait_time = rand_between(2,9);
    printf("%s is thinking for %d seconds\n", name[i], wait_time);
    sleep(wait_time);
}

/* let philosopher i eat if waiting */
void test(int i)
{
    if ((philosopher_state[i] == HUNGRY) &&
        (philosopher_state[ (i-1 < 0) ? 4 : i-1 ] != EATING) &&
        (philosopher_state[ i+1 % 5 ] != EATING)) {
        philosopher_state[i] = EATING;
        sem_post(&chopstick[i]);
    }
}

/* pick up chopsticks */
void get_chopsticks(int i)
{
    pthread_mutex_lock(&lock);
    philosopher_state[i] = HUNGRY;
    test(i);
    pthread_mutex_unlock(&lock);
    sem_wait(&chopstick[i]);
}

/* put down chopsticks */
void put_chopsticks(int i)
{
    pthread_mutex_lock(&lock);
    test( (i-1 < 0) ? 4 : i-1 );
    test( i+1 % 5 );
    pthread_mutex_unlock(&lock);
}

/* philosopher eating routine */
void eat(int i)
{
    int wait_time = rand_between(2,9);
    printf("%s is eating for %d seconds\n", name[i], wait_time);
    sleep(rand_between(1,20));
}

/* philosopher loop */
void *dine(void *index)
{
    int i = (int) index;

    loop {
        think(i);
        get_chopsticks(i);
        eat(i);
        put_chopsticks(i);
    }
}

/* create philosopher thread with index and name */
void create_philosopher(int i)
{
    int status = pthread_create(&(philosopher[i]), NULL, dine, (void *)i);
    if (status != 0)
        exit(status);
}

/* main thread entry point */
int main(int argc, char **argv)
{
    int i = 0;

    /* set random seed */
    seedp = time(NULL);

    /* initialize chopstick semaphores to 0 */
    for (i=0; i<5; ++i)
        sem_init(&(chopstick[i]), 0, 0);

    /* create philosophers */
    for (i=0; i<5; ++i)
        create_philosopher(i);

    /* exit main process while threads still running */
    pthread_exit(NULL);
}
