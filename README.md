# Interactor

A program to test solutions of interactive competitive programming problems.

## How to use

First install the binary by running `make install`.

Now, write a solution program and a program to simulate the judge (i.e., a program that reads the queries of your solution from *stdin* and responds to *stdout*). Then, compile them to their executables (let's call them `solution` and `judge`), and run `interactor solution judge`.

Check the examples to see how they work. (Run `make example`)

You can run the interactor in two modes, for different purposes:

1. Fast mode

	Default, run without any options. This can be used for the purposes of calculating worst-case time or running exhaustively to look for the reason of WA.

2. Step-by-step mode

	Run with the option flag `--verbose` or `-v`. In this mode, what the solution and the judge print will be logged to the output slowly, step-by-step. This can be used for debugging.

Hint: if you use `stderr` in the judge program (or solution program) you can also debug some stuff and use the Fast mode. The examples only use it to print if you got WA or AC, but you can also print intermediate steps and calculate the duration of some piece of your solution.	

Sources that helped me implement this:

- [http://www6.uniovi.es/cscene/CS5/CS5-05.html](http://www6.uniovi.es/cscene/CS5/CS5-05.html)
- [https://www.dca.ufrn.br/~adelardo/cursos/DCA409/node39.html](https://www.dca.ufrn.br/~adelardo/cursos/DCA409/node39.html)
