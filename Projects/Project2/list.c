/*
 * Alexander Vansteel
 * Header for queue type and queue functions
 */

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Queue Function Prototypes
List* newList(){
  List *list = (List*) malloc(sizeof(List));
  list->head = NULL;
  return list;
}

void deleteList(List *list){
  ListNode *temp;

  while(list->head != NULL){
    temp = list->head;
    list->head = list->head->nextNode;
    deleteQueue(temp->queue);
    free(temp);
  }
  free(list);
}

//check for existing identifier or add a new node
void add(char *strr, int line, List *list){
  ListNode *temp =  list->head;
  ListNode *newNode;
  char *str = (char *) malloc(sizeof(char)*128);
  strcpy(str, strr);

  if (list->head == NULL){
    newNode = (ListNode*) malloc(sizeof(ListNode));
    list->head = newNode;
    newNode->identifier = str;
    newNode->queue = newQueue();
    enqueue(line, newNode->queue);
  } else {
    while (1){
      //found a matching identifier
      if (strcmp(temp->identifier,str) == 0){
        enqueue(line, temp->queue);
        return; //return after enqueuing
      }
      if (temp->nextNode == NULL)//no matching identifiers
        break;
      temp = temp->nextNode;
    }

    //no matching identifiers section
    newNode = (ListNode*) malloc(sizeof(ListNode));
    temp->nextNode = newNode;
    newNode->identifier = str;
    newNode->queue = newQueue();
    newNode->nextNode = NULL;
    enqueue(line, newNode->queue);
  }
}

void print(List *list, FILE *fout){
  if (list->head == NULL){
    fprintf(fout,"There are no identifiers.\n");
  } else {
    ListNode *current = list->head;
    while (current != NULL){
      fprintf(fout,"Identifier: %s\n", current->identifier);
      fprintf(fout,"Line Numbers: ");
      while((current->queue->head != NULL)){
        fprintf(fout,"%d ",dequeue(current->queue));
      }
      fprintf(fout,"\n\n");
      current = current->nextNode;
    }
  }
}
