/*
Write a program to "fold" long input lines into two or more shorter lines after
the last non-blank char that occurs before the n-th column of input. Make sure
your program does something intelligent with very long lines, and if there are
no blanks or tabs before the specified column. Exercise 1-22, p. 34.


We use a word buffer when reading from stdin, flushing to the screen when the
word terminates. If we reach our column width we just immediately print a
newline; this ensures that we never print a word across the boundary column.

THIS CODE DOESN'T WORK

TODO:
- Add a hyphen to the end of a line if no blanks before n-th column?
*/

#include <ctype.h>
#include <stdio.h>

#define OUT 0          // Not in a word
#define IN 1           // In a word
#define WIDTH 3        // Output column width
#define MAXLINE 1000   // Max line length
#define MAXINPUT 10000 // Max bytes to read from stdin

void my_fold(char *out, char *in, int width) {
  int state = IN;
  char c;             // Current char
  int col = 0;        // Current column
  int out_i = 0;      // Output buffer index
  int buf_i = 0;      // Current word buffer index
  char buffer[width]; // Word buffer

  for (int i = 0; i < MAXINPUT - 1 && in[i] != EOF; i++) {
    c = in[i];

    // Word reach width limit
    if (buf_i == width) {
      // Flush
      for (int i = 0; i < buf_i; i++) {
        out[out_i++] = buffer[i];
      }
      out[out_i++] = '\n';
      buf_i = 0;
      col = 0;
      continue;
    }
    // Col reach width limit
    else if (col == width) {
      out[out_i++] = '\n';
      col = 0;
      continue;
    }

    // Beginning a word
    if (isalnum(c) && state == OUT) {
      // Flush
      for (int i = 0; i < buf_i; i++) {
        out[out_i++] = buffer[i];
      }
      state = IN;
      buf_i = 0;
      col++;
      continue;
    }

    // In middle of word
    if (isalnum(c)) {
      buffer[buf_i++] = c;
      col++;
      continue;
    }

    // Whitespace
    state = OUT;
    buffer[buf_i++] = c;
    col++;
  }

  out[out_i] = '\0'; // TODO: Or null-byte? What's best practice here?
}

int main() {
  int i, c;
  char in[MAXINPUT];     // Entirety of stdin
  char folded[MAXINPUT]; // Folded output

  // Read from stdin
  for (i = 0; (c = getchar()) != EOF && i < MAXINPUT - 1; i++) {
    in[i] = c;
  }
  in[i] = EOF;

  my_fold(folded, in, WIDTH);

  printf("Folded: \n%s", folded);

  return 0;
}
