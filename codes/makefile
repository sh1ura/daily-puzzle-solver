target : solver checker

solver : solver.c puzzlelib.c original.c 8p.c 9p.c 10p.c 11p.c
	cc -O3 -o solver solver.c

checker : checker.c puzzlelib.c original.c 8p.c 9p.c 10p.c 11p.c
	cc -O3 -o checker checker.c

clean :
	rm *~
	rm solver checker
