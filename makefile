target : solver checker

solver : solver.c puzzlelib.c original.c normal.c easy.c hard.c
	cc -O3 -o solver solver.c

checker : checker.c puzzlelib.c original.c normal.c easy.c hard.c
	cc -O3 -o checker checker.c
