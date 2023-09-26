GyeongJun Son
gson@u.rochester.edu

Creating a DFA and NFA that accepts certain strings.

The file 'Finite Automata' contains all the files that are required to run the
program.

-The file with the main function is 'Project1.c'

How to run:
1) Type 'gcc -std=c99 -Wall -Werror -o Project1 Project1.c' to compile
2) Type 'Project1' to run

How the program works:
1) First it will test a DFA that accepts exactly 'ullman' and ask
for an input.
2) You can test the DFA as many times as you want. After you enter an input,
it will tell you if it is true(accept) or false(deny) and ask for another 
input.
3) To quit the current DFA(NFA), type 'quit' as the input and the program
moves on to the next DFA or NFA.

The code contains the following DFAs and NFAs:
1) DFA that accepts exactly "ullman"
2) DFA that accepts words that start with "com"
3) DFA that accepts words with exactly three "3"s
4) DFA taht accepts binary inputs with an even number of "0"s and an odd number of "1"s
5) NFA that accepts words ending with "gs"
6) NFA that accepts words containing "mas"
7) NFA that accepts words that aren't an anagram of "codebreaker"
