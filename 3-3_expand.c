/*
Write a function that expands shorthand notations like a-z into the equivalent
complete list. Handle cases like a-b-c and a-z0-9 and -a-z. Interpret leading
and trailing hyphens literally.

TODO:
- Less duplicate code
*/

#include <stdio.h>

enum state_t {
  DEFAULT,
  UPPER,
  LOWER,
  NUM,
};

void expand(char *to, char *from) {
  enum state_t state = DEFAULT;
  char c, p;    // Current, previous characters
  char *r = to; // New pointer to output string

  while ((c = *from++)) {
    p = *(r - 1);

    // Hyphen
    if (c == '-' && state == DEFAULT) {
      if (p >= 'A' && p <= 'Z')
        state = UPPER;
      else if (p >= 'a' && p <= 'z')
        state = LOWER;
      else if (p >= '0' && p <= '9')
        state = NUM;
      continue; // Don't copy the hyphen yet
    }
    // Lowercase alpha expansion
    else if (c >= 'a' && c <= 'z' && state == LOWER) {
      if (p >= 'a' && p < c) { // Valid expansion
        // Expand up to but not including current char
        for (char x = p + 1; x < c; x++) {
          *r++ = x;
        }
        state = DEFAULT;
      }
    }
    // Uppercase alpha expansion
    else if (c >= 'A' && c <= 'Z' && state == UPPER) {
      if (p >= 'A' && p < c) {
        for (char x = p + 1; x < c; x++) {
          *r++ = x;
        }
        state = DEFAULT;
      }
    }
    // Numeric expansion
    else if (c >= '0' && c <= '9' && state == NUM) {
      if (p >= '0' && p < c) {
        for (char x = p + 1; x < c; x++) {
          *r++ = x;
        }
        state = DEFAULT;
      }
    }
    // Invalid expansion, copy the uncopied hyphen as a literal
    if (state != DEFAULT) {
      *r++ = '-';
      state = DEFAULT;
    }
    *r++ = c;
  }
  *r = '\0';
}
