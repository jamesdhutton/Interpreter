Interpreter for Simple Language
===============================

This program demonstrates how to make an interpreter for a programming language. It uses the ["Gang of Four" Intepreter design pattern](http://en.wikipedia.org/wiki/Interpreter_pattern) to implement a simple, Pascal-like language. It is written in C++ and compiles under Windows, Linux and MacOS.

## To build it
* Linux and MacOS: type `make`
* Windows: use the Visual Studio project

## Usage
`interpreter <action> <filename>`

Where action is `/p` to pretty-print or `/e` to execute

## Example
	
The grammar of the language is Pascal-like. Here is a sample program that prints the first 100 prime numbers. 

This example is available in the "Samples" directory. You can run it by typing `interpreter /e ../samples/compute_primes.txt` (use backslashes for Windows)

```
primecount := 0
testprime := 1

while primecount < 100
begin

	isprime := 1

	factor := 2
	while isprime and factor * factor < testprime + 1
	begin
		isprime := testprime mod factor <> 0
		factor := factor + 1
	end

	if isprime = 1
	begin
		print testprime
		primecount := primecount + 1

	end	

	testprime := testprime + 1

end

```
