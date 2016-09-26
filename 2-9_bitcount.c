/*
Write a faster version of bitcount, which counts the number of 1 bits in an int.

Ex 2-9, p. 51.
*/

/*
Original, from K&R C
*/
// int bitcount(unsigned x) {
//   int result = 0;
//
//   while (x != 0) {
//     // Using octal 1 here instead of int 1 maybe used to make a difference on
//     // some architectures. Simpler instruction, perhaps. Doesn't seem to
//     // change the assembly on my machine.
//     if (x & 01) {
//       result++;
//     }
//
//     x >>= 1;
//   }
//
//   return result;
// }

/*
Faster
x &= x - 1 deletes the lowest-order 1-bit.
*/
int bitcount(unsigned x) {
  int result = 0;

  while (x != 0) {
    result++;
    x &= x - 1;
  }

  return result;
}
