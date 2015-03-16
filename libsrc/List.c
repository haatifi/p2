#include <stdio.h>
#include<assert.h>
#include <stdlib.h>
#include "List.h"
/* 2015: Huma Aatifi
 * *
 *
 *
 */

struct list * createList(int (*equals)(const void *,const void *),
			 char * (*toString)(const void *),
			 void (*freeObject)(void *))
{
	struct list *list;
	list = (struct list *) malloc(sizeof(struct list));
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->equals = equals;
	list->toString = toString;
	list->freeObject = freeObject;
	return list;
}

void freeList(struct list *list)
{
   
  
	if(list == NULL)
	{
		return;
	}
	
	struct node *current = list->head;
	
	while(current != NULL)
	{
	  struct node *nextNode = current->next;
	  freeNode(current, list->freeObject);
	  current= nextNode;
	}

	 free(list);
	
}
/*
 * returns the size of the list
 * 
 */

int getSize(const struct list *list)
{
	if(list == NULL){
		return 0;
	}else{
   	 	return list->size;
	}
}


int isEmpty(const struct list *list)
{
	if(!list){
	  return 1;
	}
	else{
	
	return list->size == 0;
	}
}

void addAtFront(struct list *list, struct node *node)
{
	if (list == NULL) return;
	if (node == NULL) return;
	list->size++;
	node->next = list->head;
	node->prev = NULL;
	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
	} else {
		list->head->prev = node;
		list->head = node;
	}
}
I
void addAtRear(struct list *list, struct node *node)
{
	 if(list == NULL || node == NULL){
                 return;
          }else if(list -> size == 0)
          {
                assert(list->head==NULL);
                assert(list->tail==NULL);
                list -> head = node;
                list->tail=node;

          }
                else
                {
                list->tail -> next = node;

                node -> prev = list-> tail;

                list -> tail = node;
                node->next=NULL;
                }

        list -> size++;
        return;

		  
 
}

struct node* removeFront(struct list *list)
{
	if(list == NULL || list->size == 0){
         return NULL;
        }else{
                struct node  *temp = list->head;
                if(list->size == 1){
                        list->head = list->tail = NULL;
                }else{

                        list->head = list->head->next;
                        list -> head -> prev = NULL;

                }
                temp->prev = NULL;
                temp->next = NULL;
                list->size--;
                return temp;
        }

	return NULL;
}

struct node* removeRear(struct list *list)
{
	if(list == NULL || list->size == 0){
                 return NULL;
         }else
           {
                struct node  *temp = list->tail;
                if(list->size ==1){

        list->tail=list->head=NULL;
                }else{

                        list->tail=list->tail->prev;
                        list -> tail -> next = NULL;
                }
        temp->prev = NULL;
        temp->next = NULL;
        list->size--;
        return temp;
        }
}

struct node* removeNode(struct list *list, struct node *node)
{
	if(list == NULL || node == NULL){
                return NULL;
         }else if(list -> head == node){
                return removeFront(list);
         }else if(list->tail == node){
                return removeRear(list);
        }else{
                struct node *temp = list->head;
                while(temp != NULL){
                        if(temp == node){
                                temp->prev->next = temp->next;
                                temp->next->prev = temp->prev;
                                temp = NULL;
                                list->size--;
                                node->prev = NULL;
                                 node->next = NULL;
                                return node;

                        }else{
                                temp = temp->next;
                        }
                }

                return temp;
        }

}

struct node* search(const struct list *list, const void *obj)
{
	  if(list == NULL || isEmpty(list))
        {
                return NULL;
        }else{
                struct node * temp= list->head;
                while(temp!= NULL){
                        if((list->equals (temp -> obj, obj)) == 0){
                                return temp;
                        }else{
                                temp = temp -> next;
                        }

                } return NULL;
        }



}

void reverseList(struct list *list)
{
if(list == NULL){
    return;
  }
else{
  struct node *tmp = list -> head;
  struct node * tmp2, *theTail;

  while(tmp != NULL){
    tmp2 = tmp -> next;
    tmp -> next = tmp -> prev;
    tmp -> prev = tmp2;
    tmp = tmp2;
  }
  theTail = list -> tail;
  list -> tail = list -> head;
  list -> head = theTail;
}

}

void printList(const struct list *list)
{
	if (!list) return; //list was null!!
	int count = 0;
	char *output;
	struct node *temp = list->head;
	while (temp) {
		output = list->toString(temp->obj);
		printf(" %s -->",output);
		free(output);
		temp = temp->next;
		count++;
		if ((count % 6) == 0)
			printf("\n");
	}
	printf(" NULL \n");
}
