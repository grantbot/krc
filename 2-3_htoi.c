/*
Implement htoi. Ex 2-3, p. 46.

TODO:
- Support signed values
- Write itoh (repeatedly divide by 16, converting remainder to hex char, and
  reversing at the end?)
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Get decimal value of a single hex digit.
int chtoi(char hex) {
  hex = tolower(hex);

  if (hex >= '0' && hex <= '9') {
    return hex - '0';
  } else if (hex >= 'a' && hex <= 'f') {
    return hex - 87;
  }

  return -1;
}

long my_htoi1(char *hex) {
  int len;          // length of hex string, sans '0x' or '0X' prefix
  long decimal = 0; // return result

  // Ignore '0x' prefix
  hex = hex + 2;

  len = strlen(hex);

  // Accumulate until last digit
  for (int i = 0; i < len - 1; i++) {
    // << 4 is equiv to multiplying by 16
    decimal += chtoi(hex[i]) << ((len - 1 - i) * 4);
  }

  // Add the value of the last digit
  decimal += chtoi(hex[len - 1]);

  return decimal;
}

long my_htoi2(char *hex) {
  long decimal = 0; // return result

  // Ignore '0x' prefix
  hex = hex + 2;

  for (int i = 0; hex[i] != '\0'; i++) {
    // Each time we append a digit, the existing digits take on more
    // 'significance'. 8, when followed by a 0, represents 8 16's in hex.
    decimal = 16 * decimal + chtoi(hex[i]);
  }

  return decimal;
}
