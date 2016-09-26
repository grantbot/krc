/*
Test suite for Chapter 1 exercises.
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

  fclose(test_output);
  fclose(test_input);
}

void test_htoi(long exp_out, char *hex) { assert(my_htoi2(hex) == exp_out); }

void test_setbits(int x, int p, int n, int y, int expected) {
  assert(setbits(x, p, n, y) == expected);
}

void test_invertbits(int x, int p, int n, int expected) {
  assert(invertbits(x, p, n) == expected);
}

void test_bitcount(int x, int expected) { assert(bitcount(x) == expected); }

void test_binsearch(int *sorted, int len, int target, int expected) {
  assert(binsearch(sorted, len, target) == expected);
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

  /*Hex to int conversion*/
  test_htoi(10, "0xa");
  test_htoi(10, "0xA");
  test_htoi(15, "0xf");
  test_htoi(15, "0xF");
  test_htoi(255, "0xff");
  test_htoi(255, "0xFF");
  test_htoi(3735928559, "0xdeadbeef");
  test_htoi(3735928559, "0xDEADBEEF");

  /*setbits*/
  test_setbits(0, 6, 3, 31, 112);
  test_setbits(37, 5, 3, 229, 45);

  /*invertbits*/
  test_invertbits(37, 5, 3, 29);

  /*bitcount*/
  test_bitcount(37, 3);
  test_bitcount(229, 5);

  /*binsearch*/
  int sorted[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  test_binsearch(sorted, 10, 4, 3);
}
