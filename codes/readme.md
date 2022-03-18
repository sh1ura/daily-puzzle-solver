# C codes of the solver of "A-puzzle-a-day" and its modified puzzle.

## programs

* solver : It finds and shows the solutions. if you run this executable without arguments, it shows the solutions of all month/date. Or you can specify date to be solved by `./solver <month> <date>` in command line.
* checker : It counts the number of solutions of the all date. 

## files
* solver.c : main program of the solver
* checker.c : main program of the checker
* puzzlelib.c : support library to solve the puzzle. Common for both of solver and checker.
* original.c : definition of the original "A-puzzle-a-day" board and pieces.
* 8p.c, 9p.c, 10p.c, 11p.c : definition of the board and pieces

## How to configure

* Edit source code (puzzlelib.c) to switch 8p / 9p / 10p / 11p
* If you want to see the all solutions of spedified month and date, change the value defined for `FIND_ALL_SOLUTION` to 1.

## How to compile

* In the UNIX like environment, just run `make` in the folder.
* Here I do not use separate compilation and link manner but just direct #include-ing of C sources.

## Algorithm

* The solver finds a solution by blute-force search with recursive algorithm.
* The checker traverses the all possible piece arrangement, then check the result (position of vacant grids) to count the number of solutions for each month/date.
