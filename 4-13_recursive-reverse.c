/*
Write a recursive, in-place version of reverse(s).

p. 88.
*/

#include <stdio.h>
#include <string.h>

void do_reverse(char *s, int l, int r) {
  if (l >= r) {
    return;
  }

  register char t; // Temp

  // Swap
  t = s[l];
  s[l] = s[r];
  s[r] = t;

  do_reverse(s, ++l, --r);
}

void recursive_reverse(char *s) {
  int l = 0;
  int r = strlen(s) - 1;

  do_reverse(s, l, r);
}
