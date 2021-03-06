/*
 * Alexander Vansteel
 * Project 2
 */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_READ_LENGTH 128
#define SPECIAL 0
#define ALPHANUMERIC 1
#define DOUBLEQUOTE 2
#define SINGLEQUOTE 3
#define BLOCKCOMMENT 4
#define LINECOMMENT 5
#define BACKSLASH 6
#define ASTERISK 7

void appendChar(char* str, char c);
void handleChar(char* str, char c, int* state, List *list);
void stateAlphaNumeric(char* str, char c, int* state, List *list);
void stateSpecial(char* str, char c, int* state);
void stateDoubleQuote(char c, int* state);
void stateSingleQuote(char c, int* state);
void stateBackslash(char c, int* state);
void stateAsterisk(char c, int* state);
void stateBlockComment(char c, int* state);

int main(int argc, char* argv[]){
  FILE *fin, *fout;
  char strRead[MAX_READ_LENGTH];
  strRead[0] = '\0';
  char charRead = ';';
  int state = SPECIAL;
  List *list = newList();

  if (argc != 3){
    printf("\nERROR: Inccorect command line arguments.\n.");
    exit(1);
  }

  fin = fopen(argv[1], "r");
  fout = fopen(argv[2], "w");

  if (fin == NULL || fout == NULL){
    printf("\nERROR: Failed to open file..\n");
    exit(1);
  }

  while (fscanf(fin, "%c", &charRead) != EOF){

    if (charRead == '\n'){   //keeping track of line number
      if(state == ALPHANUMERIC)
      add(strRead, list);
      if(state != BLOCKCOMMENT)
      state = SPECIAL;

    } else {
      handleChar(strRead, charRead, &state, list);
    }
  }

  print(list, fout);

  deleteList(list);
  fclose(fin);
  fclose(fout);

  return 0;
}

void appendChar(char* str, char c){
  int len = strlen(str);
  str[len] = c;
  str[len+1] = '\0';
}

//handling the character read based on the current state helper function
void handleChar(char* strRead, char charRead, int* state, List *list){

  if (*state == ALPHANUMERIC){
    stateAlphaNumeric(strRead, charRead, state, list);
  } else if (*state == SPECIAL){
    stateSpecial(strRead, charRead, state);
  } else if (*state == DOUBLEQUOTE) {
    stateDoubleQuote(charRead, state);
  } else if (*state == SINGLEQUOTE) {
    stateSingleQuote(charRead, state);
  } else if (*state == BACKSLASH) {
    stateBackslash(charRead, state);
  } else if (*state == ASTERISK) {
    stateAsterisk(charRead, state);
  } else if (*state == BLOCKCOMMENT) {
    stateBlockComment(charRead, state);
  }
}

//state helper functions
void stateAlphaNumeric(char* strRead, char charRead, int* state, List *list) {
  if (isalpha(charRead) || isdigit(charRead)){//append character to current identifier
    appendChar(strRead, charRead);
    *state = ALPHANUMERIC;
  } else {                     //add identifier to list
    add(strRead, list);
    if (charRead == '\''){
      *state = SINGLEQUOTE;
    } else if (charRead == '\"'){
      *state = DOUBLEQUOTE;
    } else if (charRead == '/'){
      *state = BACKSLASH;
    } else {
      *state = SPECIAL;
    }
  }
}

void stateSpecial(char* strRead, char charRead, int* state){
  if (isalpha(charRead)){
    strRead[0] = '\0';
    appendChar(strRead, charRead);
    *state = ALPHANUMERIC;
  } else if (charRead == '\''){
    *state = SINGLEQUOTE;
  } else if (charRead == '\"'){
    *state = DOUBLEQUOTE;
  } else if (charRead == '/'){
    *state = BACKSLASH;
  } else {
    *state = SPECIAL;
  }
}

void stateDoubleQuote(char charRead, int* state){
  if(charRead == '\"')
    *state = SPECIAL;
}

void stateSingleQuote(char charRead, int* state){
  if(charRead == '\'')
    *state = SPECIAL;
}

void stateBackslash(char charRead, int* state){
  if (charRead == '/'){
    *state = LINECOMMENT;
  } else if (charRead == '*'){
    *state = BLOCKCOMMENT;
  } else {
    *state = SPECIAL;//should only see another \ or * if we see a lone \ first
  }
}

void stateAsterisk(char charRead, int* state){
  if (charRead == '/'){
    *state = SPECIAL;
  } else {
    *state = BLOCKCOMMENT; //still in a block comment
  }
}

void stateBlockComment(char charRead, int* state){
  if (charRead == '*')
    *state = ASTERISK;
}
