Interpreter
===========

Interpreter for a simple language, based on the "Gang of Four" design pattern, as described at http://en.wikipedia.org/wiki/Interpreter_pattern

Usage: interpreter <action> <filename>
Where action is
	/p to pretty-print
	/e to execute
	
The grammar of the language is Pascal-like. There are examples in the "Samples" directory. Here is a sample program that finds the first 100 prime numbers, which you can run by typing interpreter /e ..\samples\compute_primes.txt


primecount := 1
testprime := 1

while primecount < 100
begin

	isprime := 1

	upperbound := testprime / 2
	while upperbound > 1 and isprime = 1
	begin
		isprime := testprime mod upperbound <> 0
		upperbound := upperbound - 1
	end

	if isprime = 1
	begin
		print testprime
		primecount := primecount + 1

	end	

	testprime := testprime + 1

end

