#include <stdio.h>
#include <stdlib.h>

struct Mark {
	int x;
	int y;
};

typedef struct Mark Mark;

/* load the structure that p points to with the date from f */
void getInfo(FILE* f, Mark* p);

/* write the data stored in structure item into output file f */
void printInfo(FILE* f, Mark item);

/* compare what pointers a and b point to; to be used by qsort() */
int compare(const void* a, const void* b);

int main(){
	Mark list[100];
	Mark mark;
	int size = 0, i, col = 0;
	FILE *fin;

	fin = fopen ("lab4.dat", "r");
	if (fin == NULL){
		printf ("Cannot open file.\n");
		exit(1);
	}

	while (!feof(fin)){
		getInfo (fin, &mark);
		list[size++] = mark;
	}

	// use qsort() to sort data in list
  qsort(list, size, sizeof(Mark), compare);

	for (i = 0; i < size; i++){
		printInfo(stdout, list[i]);
		if (++col % 5 == 0)
			printf("\n");
	}
  printf("\n");

	fclose(fin);

	return 0;
}

/* complete the following helper functions */

void getInfo(FILE* f, Mark* p){
	// read two integers from the input file and
	// store them in the structure that p points to
  fscanf(f, "%d %d\n", &p->x, &p->y);
}

void printInfo(FILE* f, Mark item){
	// display each mark in format of (x, y)
	// and five marks per line
  fprintf(f, "(%d,%d) ", (int)item.x, (int)item.y);
}

int compare(const void* a, const void* b){
	// compare two structures
	// return  0 if ==
  // return -1 if a < b
	// return  1 if a > b
  struct Mark *mark1 = (struct Mark*)a;
  struct Mark *mark2 = (struct Mark*)b;

  if (mark1->y != mark2->y){
    return (int)mark2->y - (int)mark1->y;
  } else {
    return (int)mark1->x - (int)mark2->x;
  }
  return 0;
}
