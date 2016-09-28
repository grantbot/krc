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

/*
Recursive version (also handles INT_MIN)

This one's funky. The last recursive invocation writes to the first byte in s,
except when n's negative, in which case it writes to the second byte in s.
Each recursive invocation then adds one to the pointer it was given and returns
it up the call stack.

Each invocation then places a null byte after its just-written character, which
will get overwritten by each calling frame until we reach the top-most one, the
initial call, which will add the final null byte and return control.
*/
char *itoa(int n, char *s) {
  if (n == 0)
    return s;

  if (n < 0) {
    *s = '-';
    s = itoa(abs(n / 10), s + 1);
  } else {
    s = itoa(abs(n / 10), s);
  }

  *s = abs(n % 10) + '0';

  *(s + 1) = '\0'; // These will all get overwritten by the calling frame.
  return s + 1;
}

/*
Improved (handles INT_MIN)
*/
// void itoa(int n, char *s) {
//   int i = 0; // Index into output string
//   int neg = n < 0;
//
//   do {
//     s[i++] = abs(n % 10) + '0';
//   } while (n /= 10); // All non-zero values are truth-y
//
//   if (neg) {
//     s[i++] = '-';
//   }
//
//   s[i] = '\0';
//   itoa_reverse(s);
// }

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
