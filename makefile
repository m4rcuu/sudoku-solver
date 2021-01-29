# Makefile

main:	clean
	g++ sudoku-solver.cpp -o sudoku-solver
	@./sudoku-solver ./data

input:	clean
	g++ sudoku-solver.cpp -o sudoku-solver
	@./sudoku-solver

clean:
	@rm -f sudoku-solver