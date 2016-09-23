/*Solution to exercise 1-19 on p. 31*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

// Read from stdin, copy into provided buffer, return num bytes copied
int my_getline(char *dest, int lim) {
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF; i++) {
    if (c == '\n') {
      dest[i++] = '\n';
      break;
    }
    dest[i] = c;
  }

  dest[i] = '\0';
  return i;
}

// TODO: Modify passed-in pointers? Or return new arrays?
// TODO: Malloc'ing from subroutines?
void my_reverse_copy(char *to, char *from) {
  int len; // Length of passed-in string

  // Get length of input
  len = 0;
  while (*from) {
    from++;
    len++;
  }

  // Copy in reverse
  for (int i = 0; i < len; i++) {
    to[i] = *--from;
  }

  to[len] = '\0';
}

int main() {
  int len;                // Length of the current line
  char line[MAXLINE];     // Current line
  char reversed[MAXLINE]; // Current line, reversed

  while ((len = my_getline(line, MAXLINE)) > 0) {
    if (len > 1) { // len == 1 implies single \n character
      my_reverse_copy(reversed, line);
      printf("%s\n", reversed);
    }
  }

  return 0;
}
