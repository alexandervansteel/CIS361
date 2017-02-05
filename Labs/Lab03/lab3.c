#include <stdio.h>
#include <string.h>

#define LEN 4

char* strnsub (char *p, int n);

int main(){
	char line[] = "His textbook was bought from that bookstore";
	char *p1, *p2, *w1, *w2;

	// set p1 to the beginning of string line
  p1 = line;
	while (*p1){
		// set p2 to the position immediately after p1
		p2 = p1+1;
    w1 = strnsub(p1,LEN);
		while (*p2){
      w2 = strnsub(p2,LEN);
			if (strncmp(p1,p2,LEN) == 0){		// use strncmp() to compare
        printf ("the first substring: %s\n", strnsub(p1,LEN));
        printf ("the second substring: %s\n", strnsub(p2,LEN));
        return 0;
      }
      p2++;      // increment p2
		}
    p1++;        // increment p1
	}
  return 0;
}


// returns a string with the first n characters of string p

char* strnsub (char *p, int n){
	// write function definition here
  char word[n];
  int i;
  for (i=0;i<n;i++){
    word[i] = *(p+i);
  }
  word[n] = '\0';
  p = word;
  return p;
}
