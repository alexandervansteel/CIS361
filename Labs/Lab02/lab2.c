// lab2.c - measure execution time of C code

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main () {
	const int MaxSize = 75000;
	int i, j, temp;
  time_t start, end, s_array, d_array;


	// Part one: processing a statically allocated array

  start = time(NULL);
	int staticArray[MaxSize];		// declare an array

	for (i=0; i<MaxSize; i++)	{	// initialize the array with a
		staticArray[i] = MaxSize-i; // descending sequence of values
  }

	for (i=0; i<MaxSize-1; i++)	{	// bubble sort data in the array
		for (j=MaxSize-1; j>i; j--) {
			if (staticArray[j-1] > staticArray[j]) {
				temp = staticArray[j-1];
				staticArray[j-1] = staticArray[j];
				staticArray[j] = temp;
			}
    }
  }
  end = time(NULL);
  s_array = end - start;

	// Part two: processing a dynamically allocated array

  start = time(NULL);
  int *dynamicArray = (int*)malloc(sizeof(int) * MaxSize); // declare and allocate array
  for (i=0; i<MaxSize; i++) { // initialize array
    dynamicArray[i] = 0;
  }

  for (i=0; i<MaxSize-1; i++) {	// bubble sort data in the array
    for (j=MaxSize-1; j>i; j--) {
      if (*(dynamicArray + (j-1)) > *(staticArray +j)) {
        temp = *(dynamicArray + (j-1));
        *(dynamicArray +(j-1)) = *(staticArray +j);
        *(dynamicArray +j) = temp;
      }
    }
  }
  end = time(NULL);
  d_array = end - start;

	// Display the amount of time used for each part above
  printf("Time for Static Array: \t\t%lu\n", s_array);
  printf("Time for Dynamic Array; \t%lu\n", d_array);

	return 0;
}
