/*
Write a function invert(x,p,n) that returns x with the n bits that begin at
position p inverted. Ex 2-7, p. 49.

Our convention is that the lowest-order bit is at p = 0, thus the highest-order
bit in a byte is p = 7.
*/

#include <stdio.h>

int invertbits(int x, int p, int n) {
  int mask;
  int inverted;

  mask = ~(~0 << n) << (p + 1 - n); // Make n-bit mask and move into position
  inverted = ~x & mask;             // Get inverted bits to set on result
  x = x & ~mask; // Zero out desired bits so we can set them anew

  return x | inverted; // Set new inverted bits
}
