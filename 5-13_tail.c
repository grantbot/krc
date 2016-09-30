/*
Toy version of the tail program.

To run:
cc 5-13_tail.c && cat <file> | ./a.out

p. 118
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000
#define NLINES 10

int tail(char *lines[], FILE *fp, int nlines) {
  int c = 0;       // Number of seen lines
  char s[MAXLINE]; // Current string

  while (fgets(s, MAXLINE, fp) != NULL) {
    // Copy line to heap
    char *p = (char *)malloc(strlen(s) + 1);
    strcpy(p, s); // Copies null byte

    // Free the pointer we're about to overwrite. No-op on NULL ptrs.
    free(lines[c % nlines]);

    // Save heap address to ring buffer
    lines[c++ % nlines] = p;
  }

  return c % nlines;
}

int main(int argc, char const *argv[]) {
  int nlines;
  int iline; // Index of last line copied, plus 1

  // Allocate ring buffer on stack
  nlines = argc > 1 ? atoi(argv[1]) : NLINES;
  char *lines[nlines];

  // Init with null ptrs (otherwise, they're garbage stack values)
  for (int i = 0; i < nlines; i++) {
    char *p = NULL;
    lines[i] = p;
  }

  iline = tail(lines, stdin, nlines);

  // Print contents of ring buffer, skipping NULLs
  for (int i = nlines; i > 0; i--) {
    if (lines[iline] != NULL)
      printf("%s", lines[iline]);
    iline = (iline + 1) % nlines;
  }

  // Free ptrs
  for (int i = 0; i < nlines; i++)
    free(lines[i]);

  return 0;
}

/*Simpler, heap-free version.*/
// int tail(char lines[][MAXLINE], FILE *fp, int nlines) {
//   int c = 0; // Number of seen lines
//
//   while (fgets(lines[c % nlines], MAXLINE, fp) != NULL)
//     c++;
//
//   return c % nlines;
// }
//
// int main(int argc, char const *argv[]) {
//   int nlines;
//   int iline; // Index of line immediately after the last one copied to buffer
//
//   // Allocate ring buffer on stack
//   nlines = argc > 1 ? atoi(argv[1]) : NLINES;
//   char lines[nlines][MAXLINE];
//
//   iline = tail(lines, stdin, nlines);
//
//   // Print contents of ring buffer, skipping NULLs
//   for (int i = nlines; i > 0; i--) {
//     if (lines[iline] != NULL)
//       printf("%s", lines[iline]);
//     iline = (iline + 1) % nlines;
//   }
//   return 0;
// }
