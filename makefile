# Makefile

main:	clean
	g++ sudoku-solver.cpp -o sudoku-solver.exe
	@./sudoku-solver.exe ./data

input:	clean
	g++ sudoku-solver.cpp -o sudoku-solver.exe
	@./sudoku-solver.exe

clean:
	@rm -f sudoku-solver.exe