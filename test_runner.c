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

void test_itob(int n, char *s, int b, char *expected) {
  itob(n, s, b);

  while (*expected != '\0') {
    assert(*s++ == *expected++);
  }

  assert(*(s++) == '\0');
}

void test_atof(char *s, double expected) {
  double result = atof(s);
  double diff = expected - result;

  // printf("result: %.10f\n", result);
  // printf("diff: %.100f\n", diff); // Floating point imprecision!

  // Never use '==' comparisons with floating point values. They're
  // fundamentally imprecise, b/c we cannot represent in finite bits an infinite
  // decimal. Instead decide on a tolerance and assert that the difference is
  // within it.
  assert(diff < 1e-15);
}

void test_reverse(char *in, char *expected) {
  recursive_reverse(in);
  assert(strcmp(in, expected) == 0);
}

void test_strend(char *s, char *t, int expected) {
  assert(strend(s, t) == expected);
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
  char s0[20];
  test_itoa(100, s0, "100");
  test_itoa(123456, s0, "123456");
  test_itoa(-100, s0, "-100");
  test_itoa(-2147483648, s0, "-2147483648");

  /*itob*/
  char s1[20];
  // Decimal
  test_itob(10, s1, 10, "10");
  test_itob(123, s1, 10, "123");
  test_itob(-2147483648, s1, 10, "-2147483648");
  // Octal
  test_itob(8, s1, 8, "10");
  test_itob(128, s1, 8, "200");
  test_itob(-128, s1, 8, "-200");
  // Hex
  test_itob(10, s1, 16, "A");
  test_itob(17, s1, 16, "11");
  test_itob(128, s1, 16, "80");
  test_itob(-128, s1, 16, "-80");

  /*atof*/
  test_atof("-1.5", -1.5);
  test_atof("123.5678", 123.5678);
  test_atof("1.23e10", 12300000000);
  test_atof("1.23e-6", 0.00000123);

  /*recursive reverse*/
  char in[] = "abcd";
  test_reverse(in, "dcba");

  /*
  The above two lines used to look like this:
    test_reverse("abcd", "dcba");
  passing the string literal directly into the function. This fails because the
  compiler ends up passing a pointer to a global asciiz "abcd" constant living
  in the data segment of your binary. Such constants are immutable, and attempts
  to change them result in bus errors.

  `char in[] = "abcd"` still creates the global "abcd" constant (that always
  happens when you use the "" char array syntax), it just ALSO copies it onto
  main's stack frame at runtime, and then tells `in` to point to that stack
  address. After being copied into the stack, it is mutable.
  */

  /*strend*/
  test_strend("foo", "bar", 0);
  test_strend("foobar", "bar", 1);
  test_strend("foobarx", "bar", 0);
  test_strend("foobarx", "", 1);
  test_strend("foobarx", "foobarx", 1);
}
