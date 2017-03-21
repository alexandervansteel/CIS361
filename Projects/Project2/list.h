/*
 * Alexander Vansteel
 * Header for list type and list functions
 */

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
// List Structures

typedef struct ListNodeStruct {
  char *identifier;
  int count;
  struct ListNodeStruct *nextNode;
} ListNode;

typedef struct ListStruct {
  ListNode *head;
} List;

List * newList();
void deleteList(List *list);
void add(char *str, int line, List *list);
void print(List *list, FILE *fout);

#endif
