/*
 * Concurrency 3: Categorical Mutual Exclusion
 * Problem 1: Sharable Resource
 *
 * File: problem2.c
 *
 * Group 37: Taylor Alexander Brown & Lucien Armand Tamdja Tamno
 * Oregon State University
 * CS 444: Operating Systems II
 * Fall 2017
 */

#include <stdio.h>
#include <pthread.h>
#include<stdlib.h>
#include <sys/stat.h>


/* infinite loop */
#define loop while(1)

/* boolean type */
typedef enum { false, true } bool;

/* an element of the linked list*/
struct Node
{
   int data;
   struct Node *next;
}*head = NULL;

/* actions on the linked list */
enum action { ADD, DELETE, LOOKUP };


/*linked list search function*/

bool searchNode(struct Node *head, int key)
{
    while (head != NULL)
    {
        if (head-> data == key)
        {
            
            return bool-> true;
        }
        head = head->next;
    }
    return bool-> false;

}


/*linked list delection function*/

void deleteNode(struct Node **head)
{
    struct Node *temp;
 
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}


/* 
* source : https://stackoverflow.com/questions/5797548/c-linked-list-inserting-node-at-the-end
*
* single linked list bottom insertion function
*/

int addNodeBottom(int val, struct Node *head){

    //create new node
    Node *newNode = (Node*)malloc(sizeof(Node));

    if(newNode == NULL){
        fprintf(stderr, "Unable to allocate memory for new node\n");
        exit(-1);
    }

    newNode->value = val;
    newNode->next = NULL;  // Change 1

    //check for first insertion
    if(head->next == NULL){
        head->next = newNode;
        printf("added at beginning\n");
    }

    else
    {
        //else loop through the list and find the last
        //node, insert next to it
        Node *current = head;
        while (true) { // Change 2
            if(current->next == NULL)
            {
                current->next = newNode;
                printf("added later\n");
                break; // Change 3
            }
            current = current->next;
        };
    }
    return 0;
}


/*  objects sample of thread struct */

struct threadFrame {

	pthread_mutex_t *mutex;

	pthread_mutex_lock (mutex);
	pthread_mutex_unlock (mutex);

}

/* mutual exclusion lock */
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

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

/* random number between x and y inclusive */
int random_between(int x, int y)
{
    return ((unsigned int)rand_r(&seedp) % (y-x+1)) + x;
} 


/* default number of lions */
#ifndef NUMBER_THREADS
#define NUMBER_THREADSN 3
#endif

/* a thread using the linked list  at a given time */

void actionOverList( struct Node pos, int num){

	int i;
	pthread_t threadList;

	printf("Enter number of Threads %d\n");

	scanf("%d", &num);
	NUMBER_THREADS = num;

	for (i=0; i < NUMBER_THREADS; i++){

		threadList.create_threads(random_between(1,9), threadFrame->mutex[i], NULL);
	}

	
	Switch ( threadList -> action){

	/* a given thread inserting into the single linked list*/	
    case ADD:   

    	for (i=0; i < NUMBER_THREADS; i++){

			threadList.addNodeBottom(i, pos); 
    		threadList->threadFrame.pthread_mutex_lock(threadframe.mutex[i]);
		}

    	 continue;

    	case LOOKUP:

    	for (i=0; i < NUMBER_THREADS; i++){

			threadList.searchNode(pos, i); 
    		
		} 
    	
    	break;
     
    case DELETE:
    for (i=0; i < NUMBER_THREADS; i++){

			threadList.deleteNode(pos[i], i); 
    		
		} 
    	 
     break;

     default:

     printf(" no thread was created on the list\n");
     break;
    
    
    
	}

}


