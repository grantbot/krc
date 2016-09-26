/*
Write a function setbits(x,p,n,y) that returns x with the n bits that begin
at position p set to the rightmost n bits of y, leaving the other bits
unchanged. Ex 2-6, p. 49.

Our convention is that the lowest-order bit is at p = 0, thus the highest-order
bit in a byte is p = 7.
*/

#include <stdio.h>

int setbits(int x, int p, int n, int y) {
  int mask;

  mask = ~(~0 << n); // Make mask with lowest n bits set to 1
  y = y & mask;      // Get lowest n bits of y

  mask = mask << (p + 1 - n); // Left shift the mask into position
  y = y << (p + 1 - n);       // Left shift desired y bits into position

  x = x & ~mask; // Zero out desired bits in x so we can set them
  return x | y;  // Set desired y bits
}
