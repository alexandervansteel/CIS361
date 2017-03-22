/*
 * Alexander Vansteel
 *
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
    free(temp);
  }
  free(list);
}

//check for existing identifier or add a new node
void add(char *strr, int line, List *list){
  ListNode *temp =  list->head;
  ListNode *prev = list->head;
  ListNode *newNode;
  char *str = (char *) malloc(sizeof(char)*128);
  strcpy(str, strr);

  if (list->head == NULL){
    newNode = (ListNode*) malloc(sizeof(ListNode));
    list->head = newNode;
    newNode->identifier = str;
    newNode->count = 1;
  } else {
    while (1){
      //found a matching identifier
      if (strcmp(temp->identifier,str) == 0){
          temp->count++;
          prev->nextNode = temp->nextNode;
          temp->nextNode = list->head;
          list->head = temp;
        return;
      }
      if (temp->nextNode == NULL){//no matching identifiers
        break;
      }
      prev = temp;
      temp = temp->nextNode;
    }

    //no matching identifiers section
    newNode = (ListNode*) malloc(sizeof(ListNode));
    newNode->identifier = str;
    newNode->count = 1;
    newNode->nextNode = list->head;
    list->head = newNode;
    return;
  }
}

void print(List *list, FILE *fout){
  if (list->head == NULL){
    fprintf(fout,"There are no identifiers.\n");
  } else {
    ListNode *current = list->head;
    while (current != NULL){
      fprintf(fout,"Identifier: \t%s\n", current->identifier);
      fprintf(fout, "Count: \t\t\t\t%d\n", current->count);
      fprintf(fout,"\n");
      current = current->nextNode;
    }
  }
}
