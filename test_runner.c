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

void test_expand(char *to, char *from, char *expected) {
  expand(to, from);

  while (*expected != '\0') {
    assert(*to++ == *expected++);
  }

  assert(*(to++) == '\0');
}

void test_itoa(int n, char *s, char *expected) {
  itoa(n, s);

  while (*expected != '\0') {
    assert(*s++ == *expected++);
  }

  assert(*(s++) == '\0');
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

  /*expand*/
  char to[50];
  test_expand(to, "fooa-zbar", "fooabcdefghijklmnopqrstuvwxyzbar");
  test_expand(to, "foo-a-zbar", "foo-abcdefghijklmnopqrstuvwxyzbar");
  test_expand(to, "foo-a-bar", "foo-abar");
  test_expand(to, "foo-0-1ar", "foo-01ar");
  test_expand(to, "foo-0-9ar", "foo-0123456789ar");
  test_expand(to, "fA-zoo-0-9ar", "fA-zoo-0123456789ar");
  test_expand(to, "fA-Zoo-0-9ar", "fABCDEFGHIJKLMNOPQRSTUVWXYZoo-0123456789ar");
  test_expand(to, "fA-Fb-do-0-9ar", "fABCDEFbcdo-0123456789ar");
  test_expand(to, "foo-a--zbar", "foo-a--zbar");

  /*itoa*/
  char s[20];
  test_itoa(100, s, "100");
  test_itoa(123456, s, "123456");
  test_itoa(-100, s, "-100");
  test_itoa(-2147483648, s, "-2147483648");
}
