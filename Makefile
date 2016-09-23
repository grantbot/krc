test: test_runner.c 1-16-0_maxline.c 1-23_comments.c
	cc -c 1-16-0_maxline.c 1-23_comments.c 2-3_htoi.c && cc test_runner.c 1-16-0_maxline.o 1-23_comments.o 2-3_htoi.o && ./a.out
