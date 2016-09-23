/*
Remove all comments from a C program. Handle quoted strings and character
constants. C comments do not nest. Ex 1-23, p. 34.

Edge Cases:
- Comments inside quoted strings
- Not writing the '/' that closes a block comment

TODO:
- Line comments that exist on their own line will end up being a
  blank line in the output.
- Fix the hilarious bug that occurs when parsing this source code and which is
  caused by line 52 in which the '\\' puts us into a QUOTE state we don't exit
  until the "we're" in line 61, b/c the second half of '\\' is parsed as an
  escaped quote and is thus insufficient to put us back to DEFAULT state.
  The apostrophe in "we're" is what gets us back.
*/

#include <stdio.h>

enum state_t {
  DEFAULT, // Default copying state
  BLOCK_C, // Block comment
  LINE_C,  // Line comment
  QUOTE,   // Single or double quote
};

void strip_comments(FILE *out, FILE *in) {
  char c;        // Current character
  char prev = 0; // Previously read character
  enum state_t state = DEFAULT;

  while ((c = fgetc(in)) != EOF) {
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
    if (prev && (state == DEFAULT || state == QUOTE)) {
      fputc(prev, out);
    }

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
  if (state == DEFAULT || state == QUOTE) {
    fputc(prev, out);
  }
}

/*Comment out for testing in compiled test runner*/
// int main() {
//   strip_comments(stdout, stdin);
//   fclose(stdout);
//   fclose(stdin);
//   return 0;
// }
