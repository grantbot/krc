test: test_runner.c 1-16-0_maxline.c 1-23_comments.c 2-6_setbits.c 2-7_invert.c
	cc -c 1-16-0_maxline.c 1-23_comments.c 2-3_htoi.c 2-6_setbits.c 2-7_invert.c && cc test_runner.c 1-16-0_maxline.o 1-23_comments.o 2-3_htoi.o 2-6_setbits.o 2-7_invert.o && ./a.out
