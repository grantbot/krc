/*
Toy quicksort implementation that accepts pointers for the comparison func.

To run:
cc 5_qsort.c && cat <file> | ./a.out

p. 119
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEMAX 1000  // Max line length
#define MAXLINES 5000 // Max #lines to be sorted

int readlines(char *lines[], FILE *fp, int maxlines) {
  char *p = NULL;     // Pointer for a heap address
  char line[LINEMAX]; // Buffer for current line
  int n;              // Number of lines read
  int len;            // Len of current line

  n = 0;
  while ((fgets(line, LINEMAX, fp)) != NULL) {
    if ((len = strlen(line)) == 1) // Skip blank lines
      continue;

    if (n > maxlines || (p = (char *)malloc(len + 1)) == NULL)
      return 1; // Too much!

    strcpy(p, line);

    if (p[len - 1] == '\n') // Strip trailing newline
      p[len - 1] = '\0';

    while (*p == ' ' || *p == '\t') // Strip leading blank space
      p++;

    lines[n++] = p;
  }

  return n;
}

void swap(char *l[], int i, int j) {
  char *t;

  t = l[i];
  l[i] = l[j];
  l[j] = t;
}

void _qsort(char *lines[], int l, int r, int (*comp)(void *, void *)) {
  int last; // Last swapped index

  if (l >= r)
    return;

  swap(lines, l, (l + r) / 2); // Swap partition to beginning

  last = l;

  // Loop to r starting from element after the just-swapped partition,
  // swapping to the left side of the array as we go.
  for (int i = l + 1; i <= r; i++)
    if (comp(lines[i], lines[l]) < 0)
      swap(lines, i, ++last);

  // Swap partition with the last element that's smaller than it
  swap(lines, l, last);
  _qsort(lines, last + 1, r, comp);
  _qsort(lines, l, last - 1, comp);
}

int main(int argc, char const *argv[]) {
  int nlines; // Num lines read from input
  char *lines[MAXLINES];

  nlines = readlines(lines, stdin, MAXLINES);

  _qsort(lines, 0, nlines - 1, (int (*)(void *, void *))strcmp);

  for (int i = 0; i < nlines; i++)
    printf("%s\n", lines[i]);

  return 0;
}
