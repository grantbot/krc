/*
Write strend(s,t) which returns 1 if string s occurs at the end of string t
and zero otherwise

p. 107
*/

#include <stdio.h>
#include <string.h>

int strend(char *s, char *t) {
  char *sp = s;
  char *tp = t;

  while (*tp++)
    ;
  while (*sp++)
    ;

  while (sp-- > s && tp-- > t) {
    if (*sp != *tp)
      return 0;
  }

  return 1;
}
