/*
Remove all comments from a C program. Handle quoted strings and character
constants. C comments do not nest. Ex 1-23, p. 34.

Edge Cases:
- Comments inside quoted strings
- Not writing the '/' that closes a block comment

TODO:
- Line comments that exist on their own line will end up being a
  blank line in the output.
*/

#include <stdio.h>

#define MAXLINE 1000   // Max line length
#define MAXINPUT 10000 // Max bytes to read from stdin

enum state_t {
  DEFAULT, // Default copying state
  BLOCK_C, // Block comment
  LINE_C,  // Line comment
  QUOTE,   // Single or double quote
};

void strip_comments(char *out, char *in) {
  char c;        // Current character
  char prev = 0; // Previously read character
  enum state_t state = DEFAULT;

  for (int i = 0; i < MAXINPUT - 1 && in[i] != EOF; i++) {
    c = in[i];

    // Potentially enter a non-default state
    switch (c) {
    case '/': // Line comment
      if (prev == '/' && state == DEFAULT) {
        state = LINE_C;
      }
      break;
    case '*': // Block comment
      if (prev == '/' && state == DEFAULT) {
        state = BLOCK_C;
      }
      break;
    // We handle enter AND exit of the QUOTE state up here instead of 'enter'
    // here and 'exit' down below to avoid entering and exiting the QUOTE state
    // on the same loop iteration. An unescaped quote character is ambiguous;
    // it both starts and ends a quoted string.
    case '\'': // Quote
    case '\"':
      if (prev != '\\') {
        if (state == DEFAULT)
          state = QUOTE;
        else if (state == QUOTE)
          state = DEFAULT;
      }
      break;
    }

    // Write if we're in an allowed state
    if (prev && (state == DEFAULT || state == QUOTE))
      *out++ = prev;

    // Potentially switch back to default state
    switch (c) {
    case '\n': // End line comment
      if (state == LINE_C) {
        state = DEFAULT;
      }
      break;
    case '/': // End block comment
      if (prev == '*' && state == BLOCK_C) {
        state = DEFAULT;
        // Avoid writing this '/'
        prev = 0;
        continue;
      }
    }

    prev = c;
  }
}

int main() {
  int i, c;
  char in[MAXINPUT];       // Entirety of stdin
  char stripped[MAXINPUT]; // Folded output

  // Read from stdin
  for (i = 0; (c = getchar()) != EOF && i < MAXINPUT - 1; i++) {
    in[i] = c;
  }
  in[i] = EOF;

  strip_comments(stripped, in);

  printf("%s\n", stripped);

  return 0;
}
