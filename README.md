# sudoku-solver

sudoku-solver can solve sudoku problem in a simple way. You can pass it file for instance ```.\data``` which contains 81 cells or just enter the data in the console. It is not necessary to enter data in a grid 9x9. You can pass it one by one.

```
3 0 6 5 0 8 4 0 0
5 2 0 0 0 0 0 0 0
0 8 7 0 0 0 0 3 1
0 0 3 0 1 0 0 8 0
9 0 0 8 6 3 0 0 5
0 5 0 0 9 0 6 0 0
1 3 0 0 0 0 2 5 0
0 0 0 0 0 0 0 7 4
0 0 5 2 0 6 3 0 0
```

## makefile

You can use ```makefile``` to compile file and run the program. You can press it into the console:
- ```make main``` or just ```main``` to remove last compiled program, compile another one and run it with ```./data```,
- ```make input``` remove last compiled program, compile another one and run it in input mode. It is necessary to enter data into the console,
- ```make clean``` remove last compiled program.

This was written with a ton of help from [this blog post](https://www.tutorialspoint.com/sudoku-solver-in-cplusplus) by Arnab Chakraborty.