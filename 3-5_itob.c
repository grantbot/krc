/*
Write a function itob(n, s, b) that converts an int into a base b character
representation in the string s.

P. 64.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Same as in itoa, don't feel like changing Makefile
void itob_reverse(char *s) {
  int i, j;
  char t;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    t = s[i];
    s[i] = s[j];
    s[j] = t;
  }
}

void itob(int n, char *s, int b) {
  int i = 0; // Index into output string
  int neg = n < 0;

  do {
    s[i++] = chars[abs(n % b)];
  } while (n /= b); // All non-zero values are truth-y

  if (neg) {
    s[i++] = '-';
  }

  s[i] = '\0';
  itob_reverse(s);
}
