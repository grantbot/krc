/*
Modify a naive itoa to handle the largest negative two's complement value.

If n is the most negative value for a given type, e.g. 1000000 for chars,
flipping the bits and adding 1 will just give you the same thing back, 1000000.

In such cases, n = -n will not change the value of n.

P. 64.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Same as in itob, don't feel like changing Makefile
void itoa_reverse(char *s) {
  int i, j;
  char t;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    t = s[i];
    s[i] = s[j];
    s[j] = t;
  }
}

/*Improved*/
void itoa(int n, char *s) {
  int i = 0; // Index into output string
  int neg = n < 0;

  do {
    s[i++] = abs(n % 10) + '0';
  } while (n /= 10); // All non-zero values are truth-y

  if (neg) {
    s[i++] = '-';
  }

  s[i] = '\0';
  itoa_reverse(s);
}

/*Original*/
// void itoa(int n, char *s) {
//   int i = 0;
//   int sign = n;
//
//   if (sign < 0) {
//     n = -n;
//   }
//   do {
//     s[i++] = n % 10 + '0';
//   } while ((n /= 10) > 0);
//
//   if (sign < 0) {
//     s[i++] = '-';
//   }
//
//   s[i] = '\0';
//   reverse(s);
// }
