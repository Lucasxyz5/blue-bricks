# blue-bricks
A toy language and compiler built using C++. Written with the help of "Let's Build a Compiler" by Jack Crenshaw.
IMPORTANT: This project is built to work with the target: x86_64-apple-darwin23.5.0
You can see yur target by running: "clang --version".
This code might run on other x86_64 apple systems. It will not run on any other system.

compile with: 
g++ -std=c++11 Cradle.cpp -o Cradle
run compiler with: 
./comp < code.txt > output.s
assemble with: 
clang output.s -o output
run with: 
./output
to see output:
echo $?