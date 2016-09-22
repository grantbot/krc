/*Based on example code on p. 29*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define MAXFILE 10000

// Assume caller knows to[] is big enough
void my_copy(char *to, char *from) {
  while ((*to++ = *from++))
    ;
}

int maxline(char *longest, char *input) {
  int c;              // Current input char
  int li = 0;         // Index in current line buffer
  int len = 0;        // Length of the current line
  int max = 0;        // Length of the longest line so far
  char line[MAXLINE]; // Current line buffer

  for (int i = 0; i < MAXFILE && (c = input[i]) != EOF; i++) {
    // End of line
    if (c == '\n') {
      // New longest line
      if (len > max) {
        line[li] = '\0';
        max = len;
        // I'd use strcpy but input isn't
        // a string, it's raw bytes from stdin.
        my_copy(longest, line);
      }
      // Reset current line buffer and index
      len = li = 0;
      continue;
    }
    // Copy value into current line buffer
    line[li++] = c;
    len++;
  }
  return max;
}

/*Below commented for use in compiled test suite*/
// int main() {
//   int i, c;
//   int longest_len;       // Length of longest line
//   char input[MAXFILE];   // Entirety of stdin
//   char longest[MAXLINE]; // Longest line
//
//   // Read from stdin
//   for (i = 0; (c = getchar()) != EOF && i < MAXFILE - 1; i++) {
//     input[i] = c;
//   }
//   input[i] = EOF;
//
//   longest_len = maxline(longest, input);
//
//   printf("Longest line: %s\n", longest);
//   printf("Length: %d\n", longest_len);
//
//   return 0;
// }
