#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <unistd.h>
#include "functions.h"



int main(int argc, const char *argv[]) {
    initial_screen();

    initscr();
    clear(); // clear the screen

    noecho(); // prevents letters from showing on the screen
    cbreak(); // enter is not required
    curs_set(0); // Hide the cursor

    srand(static_cast<unsigned int>(time(0))); // introduces randomness, in this case to the position of F
    Setup();

    while (!gameOver) {
        initialise_bricks();
        while (!gameOver && sum_bricks()) {
            Draw();
            Input();
            Logic();
            usleep(100000);
        }
        level++;
        // Sleep for a short period to slow down the game loop
    }

    endwin(); // End ncurses mode

    std::cout << "Game over. You reached level " << level-1 << std::endl;

    return 0;
}
