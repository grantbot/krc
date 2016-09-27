#include <stdio.h>

int maxline(char *longest, char *input);
void strip_comments(FILE *out, FILE *in);
long my_htoi1(char *hex);
long my_htoi2(char *hex);
int setbits(int x, int p, int n, int y);
int invertbits(int x, int p, int n);
int bitcount(int x);
int binsearch(int *sorted, int len, int target);
void expand(char *to, char *from);
void itoa(int n, char *s);
