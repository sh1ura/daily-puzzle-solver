# C codes of the solver for "A-puzzle-a-day" and my "Daily puzzle"

## programs

* solver : It finds and shows the solutions. if you run this executable program without arguments, it shows the solutions of all month/date. Or you can specify a single day to be solved by `./solver <month> <date>` in command line.
* checker : It counts the number of solutions of the all day in a year. 

## files
* solver.c : main program of the solver
* checker.c : main program of the checker
* puzzlelib.c : support library to solve the puzzle. Common for both of solver and checker.
* original.c : definition of the original "A-puzzle-a-day" board and pieces.
* 8p.c, 9p.c, 10p.c, 11p.c : definition of the board and pieces

## How to configure

* Edit source code (puzzlelib.c) to switch original / 8p / 9p / 10p / 11p
* If you want to see the all solutions of specified day, change the value defined for `FIND_ALL_SOLUTION` to 1.

## How to compile

* In the UNIX like environment, just run `make` in the folder.
* Here I do not use separate compilation / link scheme but just direct #include -ing of several C sources.
* The program can be used in the environment that satisfies `sizeof(unsigned long long int) >= 8` (such as GCC, Visual C, etc).

## Algorithm

* The solver finds a solution by blute-force search with recursive algorithm.
* The checker traverses the all possible piece arrangement, then check the result (position of vacant grids) to count the number of solutions for each month/date.
