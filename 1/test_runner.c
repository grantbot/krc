/*
Test suite for Chapter 1 exercises.

To run from krc/1:
cc -c 1-16-0_maxline.c && cc test_runner.c 1-16-0_maxline.o && ./a.out

 */
#include <assert.h>
#include <string.h>

#include "solutions.h"

void test_maxline(char *input, int exp_max, char *exp_longest) {
  char longest[50];
  int max;

  max = maxline(longest, input);

  assert(max == exp_max);
  assert(strcmp(longest, exp_longest) == 0);
}

void test_fold(char *in, char *out, char *expected, int width) {
  my_fold(out, in, width);
}

int main() {
  /* maxline */
  char input1[7] = {'a', 'b', 'c', '\n', 'd', 'e', '\n'};
  test_maxline(input1, 3, "abc");
  char input2[7] = {'a', 'b', '\n', 'd', 'e', 'f', '\n'};
  test_maxline(input2, 3, "def");

  /* fold */
  int width = 3;
  char in[] = "abc\tdef\n";
  char out[50];
  char expected[] = "abc\n\tde\nf\n";
  test_fold(in, out, expected, width);
}
