#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ncurses.h>
#include <cstdlib>
#include <iostream>
#include <limits>

// Constants
const int width = 21;
const int height = 20;

// Enum for direction control
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

// External variable declarations
extern bool gameOver;
extern int x, y, xB, yB; // xB and yB refer to the bullet position
extern int vx, vy; // x and y components of the bullet
extern int length;
extern int lives;
extern int level;
extern int bricks[height][width];
extern eDirection dir;

// Function declarations
void initialise_bricks();
int sum_bricks();
void initialise_ball();
void Setup();
void Draw();
void Input();
void live_lost();
void paddle_collision();
void wall_collision();
void brick_collision();
void Logic();
void initial_screen();

#endif // FUNCTIONS_H
