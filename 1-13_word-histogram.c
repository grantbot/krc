/*Solution to exercise 1-13, p. 24*/
#include <stdio.h>

#define OUT 0  // Not in a word
#define IN 1  // In a word

int main() {
  int c, curr_word_len, state;
  int length_freqs[50] = {0};  // 50-char max for words

  curr_word_len = state = 0;

  while ((c = getchar()) != EOF) {
    // Whitespace, no longer in word
    if (c == '\t' || c == '\n' || c == ' ') {
      if (state == IN) {
        state = OUT;
        length_freqs[curr_word_len]++;
        curr_word_len = 0;
      }
    }
    // We're in a word
    else {
      state = IN;  // Usually redundant, yolo
      curr_word_len++;
    }
  }

  printf("Word Length Histogram:\n");

  int freq;
  for (int len = 0; len < 50; len++) {
    freq = length_freqs[len];
    if (freq > 0) {
      printf("%2d| ", len);
      for (int i = 0; i < freq; i++)
        printf("+");
      printf("\n");
    }
  }
}
