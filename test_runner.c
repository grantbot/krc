/*
Test suite for Chapter 1 exercises.

To run from krc/1:
cc -c 1-16-0_maxline.c 1-23_comments.c && cc test_runner.c 1-16-0_maxline.o
1-23_comments.o && ./a.out

 */
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "solutions.h"

void test_maxline(char *input, int exp_max, char *exp_longest) {
  char longest[50];
  int max;

  max = maxline(longest, input);

  assert(max == exp_max);
  assert(strcmp(longest, exp_longest) == 0);
}

void test_comment_strip(int *in, char *exp_out) {
  int c;
  FILE *test_output = tmpfile();
  FILE *test_input = tmpfile();

  while ((c = *in++))
    fputc(c, test_input);

  rewind(test_input);
  strip_comments(test_output, test_input);
  rewind(test_output);

  while ((c = fgetc(test_output)) != EOF)
    assert(c == *exp_out++);
}

int main() {
  /* maxline */
  char input1[7] = {'a', 'b', 'c', '\n', 'd', 'e', '\n'};
  test_maxline(input1, 3, "abc");
  char input2[7] = {'a', 'b', '\n', 'd', 'e', 'f', '\n'};
  test_maxline(input2, 3, "def");

  /*Comment stripping*/
  int input3[8] = {'/', '*', 'a', '*', '/', 'b', 'c', '\0'};
  test_comment_strip(input3, "bc");
}
