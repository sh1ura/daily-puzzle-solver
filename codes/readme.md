# C codes of the solver of "A-puzzle-a-day" and its modified puzzle.

## programs

* solver : Find and show solutions. if you run this executable without arguments, it shows the solutions of all month/date. Or you can specify the date by `./solver <month> <date>` style.
* checker : Count the number of solutons of the all date. 

## files
* puzzlelib.c : support library to solve the puzzle. Common for both of solver and checker.
* solver.c : main program of the solver
* checker.c : main program of the checker
* original.c : definition of the original "A-puzzle-a-day" board and pieces.
* easy.c : definition of the easier version with 10 pieces. 
* normal.c : definition of the moderate version with 9 pieces.
* hard.c : definiton of the harder version with 8 pieces.

## How to compile

* In the UNIX like environment, just run `make` in the folder.

## Algorithm

* The solver just find the solution with blute-force search with recursive algorithm.
* The checker traverses the all possible piece arrangement, then check the result (vacant grids) to count the number of solutions for each month/date.
