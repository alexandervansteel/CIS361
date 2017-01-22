#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main () {
  char ch;
  int words = 0;
  int symbols = 0;
  int w_cnt = 0;
  int s_cnt = 0;

  printf ("Enter text (Ctrl-D to quit).\n");
  while ( ch = getchar(), ch != EOF ) {
    if ((isalnum(ch) != 0) || (ch == "_")) {
      w_cnt++;
    }
    if ((isalnum(ch) == 0) && (ch != "_") && (isspace(ch) == 0)) {
      s_cnt++;
    }
    if (isspace(ch) != 0) {
      if (w_cnt > 0) {
        words++;
        w_cnt = 0;
      }
      if (s_cnt > 0) {
        symbols++;
        s_cnt = 0;
      }
    }
    putchar(ch);
  }

  printf("Word Count: %d\n", words);
  printf("Symbol Count: %d\n", symbols);

  return 0;
}
