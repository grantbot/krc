/*
Write a program that replaces tabs in the input with the proper number
of blanks to space to the next tab stop. Ex 1-20, p. 34.
*/

#include <stdio.h>

#define TAB_SPACES 4

int main() {
  int i; // Loop index
  int c; // Current character

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      for (i = 0; i < TAB_SPACES; i++) {
        putchar(' ');
      }
    } else {
      putchar(c);
    }
  }

  return 0;
}
