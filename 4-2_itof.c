/*
Write a function itof(s) that converts a string into a floating-point value.
Extend it to handle scientific notation, e.g. "123.45e-6"

p. 73.
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>

double itof(char *s) {
  double val;
  double exp_power;              // To handle exponential notation
  double frac_power;             // To place the decimal at the end
  signed int val_sign, exp_sign; // 1 or -1

  // Get sign
  val_sign = *s == '-' ? -1 : 1;
  if (*s == '-' || *s == '+')
    s++;

  // Accum until decimal, if any
  for (val = 0.0; isdigit(*s); s++)
    val = 10.0 * val + (*s - '0');

  // Skip decimal
  if (*s == '.')
    s++;

  // Accum until 'e' or 'E', increasing the amount by which we'll divide at
  // the end.
  for (frac_power = 1.0; isdigit(*s); s++) {
    val = 10.0 * val + (*s - '0');
    frac_power *= 10.0;
  }

  val = val_sign * val / frac_power;

  // Handle exponential notation
  if (*s == 'e' || *s == 'E') {
    exp_sign = *++s == '-' ? -1 : 1;

    if (*s == '-')
      s++;

    for (exp_power = 0.0; isdigit(*s); s++)
      exp_power = 10.0 * exp_power + (*s - '0');

    return val * pow(10.0, (exp_sign * exp_power));
  }

  return val;
}

/*Original*/
// double itof(char *s) {
//   double val;
//   int power;
//   int sign; // 1 or -1
//
//   // Get sign
//   sign = *s == '-' ? -1 : 1;
//   if (*s == '-' || *s == '+')
//     s++;
//
//   // Accum until decimal, if any
//   for (val = 0.0; isdigit(*s); s++)
//     val = 10.0 * val + (*s - '0');
//
//   // Skip decimal
//   if (*s == '.')
//     s++;
//
//   // Accum until end of string, increasing the amount by which we'll divide
//   at
//   // the end.
//   for (power = 1; isdigit(*s); s++) {
//     val = 10.0 * val + (*s - '0');
//     power *= 10;
//   }
//
//   return sign * val / power;
// }
