#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX 25

typedef int EType;		// type of elements in stack
typedef int BOOLEAN;

typedef struct {
  EType data[MAX];
  int top;
} STACK;

void initialize(STACK *pS){ 	// initialze the stack
  pS->top = -1;
}

BOOLEAN isEmpty(STACK *pS){ 	// returns true if the stack is empty
  if (pS->top == -1){
    return TRUE;
  } else {
    return FALSE;
  }
}

BOOLEAN isFull(STACK *pS){  	// returns true if the stack is full
  if (pS->top == MAX - 1){
    return TRUE;
  } else {
    return FALSE;
  }
}

BOOLEAN pop(STACK *pS, EType *px){	// removes the top element from the stack
  // has px point to the removed element
  // returns true if done successfully
  if (!isEmpty(pS)){
    *px = pS->data[pS->top];
    pS->top--;
    printf("Pop from Stack.\n");
    return TRUE;
  } else {
    printf("ERROR: POP -> Stack is empty, unable to POP.\n");
    return FALSE;
  }
}

BOOLEAN push(EType x, STACK *pS){
  // puts an element on the top of the stack
  // returns true if done successfully
  if (!isFull(pS)){
    pS->top++;
    pS->data[pS->top] = x;
    printf("Push to Stack.\n");
    return TRUE;
  } else {
    printf("ERROR: PUSH -> Stack is full. Unable to PUSH.\n");
    return FALSE;
  }
}

int main(){
  STACK s;
  int i = 0;

  initialize(&s);

  // write code below to test functions defined above
  while (i < MAX+1){
    if (!push(i, &s)){
      while (i > -2){
        if (!pop(&s, &i)){
          return 0;
        }
      }
    }
  }
  return 0;
}
