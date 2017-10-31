#include<stdio.h>
#include<stlib.h>
#include<linux/list.h>
#include<linux/types.h>


/* data structure to define the relationship between floor*/
struct current_floor{


	struct current_floor *next, *prev;

	}

// function to recursively sort lists

void mergeSort(current_floor** head)
{
  	current_floor* list1;
  	current_floor* list2;
  	/* Base case -- length 0 or 1 */
  	if ((*head == NULL) || ((*head)->next == NULL))
  	{
    	return;
  	}
 
  	// Split list(head) into 'list1' and 'list2' sublists 
  	splitLL(*head, &list1, &list2); 
 
  	/* Recursively sort the sublists */
  	mergeSort(&list1);
  	mergeSort(&list2);
  	//merge the two sorted lists together
  	*head = mergeSortedLists(list1, list2);
}

//Merge the two sorted lists
current_floor* mergeSortedLists(current_floor* list1, current_floor* list2)
{
 
  current_floor* result = NULL;
 
  /* Base cases */
  if (list1 == NULL)
     return(list2);
  else if (list2==NULL)
     return(list1);
 
  /* Pick either list1 or list2, and recur */
  if (list1 != NULL)
  {
    list1->next = mergeSortedLists(list1->next,list2);
    list1->next->prev = list1;
    list1->prev = NULL;
    return list1;
  }
  else
  {
    list2->next = mergeSortedLists(list1,list2->next);
    list2->next->prev = list2;
    list2->prev = NULL;
    return list2;
  }
}

//split the nodes into two halves 
void splitLL(current_floor* head,
          current_floor** list1, current_floor** list2)
{
  current_floor* fast;
  current_floor* slow;

  if (head==NULL || head->next==NULL)
  {
    /* length < 2 cases */
    *list1 = head;
    *list2 = NULL;
  }
  else
  {
    slow = head;
    fast = head->next;
 
    // Move 'fast' two nodes, and move 'slow' one node //
    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
      at that point. */
    *list1 = head;
    *list2 = slow->next;
    slow->next = NULL;
  }
}




int main (int argc, char *argv[] ){

	list1 = malloc(sizeof(struct current_floor));
	int* list2 =

	char* list1 = [1,2,9,10,14,5], *list2=[3,3,7,8,13,12];

	mergeSort(list1,list2);

	printf(" this is the evelavor layout %s\n",mergeSort() );




return 0;
}