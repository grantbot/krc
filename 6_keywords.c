/*
Count the occurrences of keywords in a C program.

To run:
cc 6_keywords.c && cat <file> | ./a.out

p. 133
*/

#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define WORDMAX 100 // Max word length

struct kw {
  char *word;
  int count;
};

struct kw kwtable[] = {
    {"auto", 0},  {"break", 0},    {"case", 0},    {"char", 0},
    {"const", 0}, {"continue", 0}, {"default", 0}, {"for", 0},
    {"int", 0},   {"struct", 0},   {"void", 0},    {"while", 0},
};

/*
Read a word or char from a stream. Returns length of word, 0 on EOF.
*/
int getword(char *word, FILE *fp, int max) {
  int c;     // Current char
  int n = 0; // Number of chars seen in current word

  while ((c = getc(fp)) != EOF && !isalpha(c))
    ;

  for (; c != EOF && isalpha(c) && n < max; c = getc(fp)) {
    *word++ = c;
    n++;
  }

  *word = '\0';
  return n;
}

/*
Search for a keyword string in a sorted array of kw structs.
Returns pointer to containing struct, if string is found, and NULL otherwise.
*/
struct kw *binsearch(char *t, struct kw kwtable[], int l, int r) {
  if (l > r)
    return NULL;

  int m = (l + r) / 2;
  int cmp;

  if ((cmp = strcmp(t, kwtable[m].word)) == 0)
    return kwtable + m;
  else if (cmp < 0)
    return binsearch(t, kwtable, l, m - 1);
  else
    return binsearch(t, kwtable, m + 1, r);
}

int main(int argc, char const *argv[]) {
  int nkeys; // Number of keys in lookup array
  char word[WORDMAX];
  struct kw *kwptr;

  nkeys = sizeof kwtable / sizeof(struct kw);

  while ((getword(word, stdin, WORDMAX)) > 0)
    if ((kwptr = binsearch(word, kwtable, 0, nkeys - 1)))
      kwptr->count++;

  for (int i = 0; i < nkeys; i++)
    printf("%-10s %d\n", kwtable[i].word, kwtable[i].count);

  return 0;
}
