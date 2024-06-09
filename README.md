paddle game

to compile on mac (with only main.cpp and functions.h) type:
g++ -std=c++20 main.cpp -o game -lncurses
where "game" is the name that will be called later ./game to run it from the terminal

when using main.cpp, functions.h and functions.cpp, type:
g++ -std=c++20 -o game main.cpp functions.cpp -lncurses
and run as in the case above
