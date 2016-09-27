test: test_runner.c 1-16-0_maxline.c 1-23_comments.c 2-6_setbits.c 2-7_invert.c 2-9_bitcount.c 3-1_binsearch.c 3-3_expand.c
	cc -c 1-16-0_maxline.c 1-23_comments.c 2-3_htoi.c 2-6_setbits.c 2-7_invert.c 2-9_bitcount.c 3-1_binsearch.c 3-3_expand.c && cc test_runner.c 1-16-0_maxline.o 1-23_comments.o 2-3_htoi.o 2-6_setbits.o 2-7_invert.o 2-9_bitcount.o 3-1_binsearch.o 3-3_expand.o && ./a.out
