#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ncurses.h> // Include necessary libraries
#include <cstdlib>
#include <iostream>
#include <limits>

extern bool gameOver;

const int width = 21;
const int height = 20;
extern int x, y, xB, yB; // xB and yB refer to the bullet position
extern int vx, vy; // x and y components of the bullet

extern int length;
extern int lives;
extern int level;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
extern eDirection dir;

extern int bricks[height][width];

inline void initialise_bricks() {
    for (int i = 0; i < height; i++) { // Fixed array bounds
        for (int j = 0; j < width; j++) {
            if (i < (height - 2) && i > (height - 8) && j > (width/2-3) && j < (width/2+3)) {
                bricks[i][j] = rand() % 2;
            } else {
                bricks[i][j] = 0;
            }
            
//                if (i < (height - 2) && i > (height - 5) && j > 8 && j < 12) {
//                    bricks[i][j] = 1;
//                } else {
//                    bricks[i][j] = 0;
//                }
            
            
        }
    }
}

inline int sum_bricks() {
    int sum = 0;
    for (int i = 0; i < height; i++) { // Fixed array bounds
        for (int j = 0; j < width; j++) {
            sum += bricks[i][j];
        }
    }
    return sum;
}

inline void initialise_ball() {
    vx = (rand() % 2 == 0) ? 1 : -1;
    vy = 1;
    xB = width / 2;
    yB = rand() % ((height - 1) / 2) + 0*height/2;
    
//    vx = 1;
//    vy = 1;
//    xB = 7;
//    yB = 14;
}

inline void Setup() {
    initialise_ball();
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = 1;
}

inline void Draw() {
    clear(); // ncurses function to clear the screen
    
    printw("level  %d", level);
    printw("\n");
    for (int i = 0; i <=width ; i++) // drawing the lower line
    {
        printw("#");
    }
    printw("\n");

    for (int i = height; i > 0; i--)
    {
        for (int j = 0; j <=width; j++)
        {
            if ( (i==y) &&  (j<=x+length/2) && (j>=x-length/2) ) //paddle
            {
                printw("=");
            }
            else if (j == 0 || j==width)
            {
                printw("#");
            }
            else if (bricks[i][j]==1)
            {
                printw("o");
            }
            else if (i==yB && j==xB) //draw the ball
                {
                    printw("O");
                }
            else
                {
                    printw(" ");
                }
            
        }
        printw("\n");
    }

    for (int i = 0; i <=width; i++)
    {
        printw("#");
    }
    printw("\n");
    
    
    printw("\n");
    printw("to move press: \n");
    printw("left->a; right->d \n");
    printw("up->w; down->s (no more than at y=3) \n");
    printw("\n vx: %d", vx);
    printw("\n vy: %d", vy);
    printw("\n x: %d", xB);
    printw("\n y: %d", yB);
    printw("\n lives: %d", lives);
    printw("\n bricks left: %d", sum_bricks());

    refresh(); // Refresh the screen to show the changes
}
inline void Input() {
    nodelay(stdscr, TRUE); // if uncommented then it behaves as if the button was always pressed
    int ch = getch();      // Get user input
    if (ch != ERR) {       // If a key was pressed
        switch (ch) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            default:
                dir = STOP; // if the button is anything other than a,d,x then dont do anythign
                break;
        }
    } else {
        dir = STOP;
    }
}

inline void live_lost() // checks if the ball goes past the paddle
{
    if (yB == 0) { // goes past the paddle
        lives--;
        if (lives <= 0) {
            gameOver = true;
        }
        initialise_ball();
    }
}

inline void paddle_collision() {
    // keeping a 3 variant form here to make corrections easier
    if (yB + vy == y && (xB + vx == x || xB + vx == x + 1 || xB + vx == x - 1)) { //paddle colision
        vy = -vy;
        vx = rand() % 3 - 1;

    } else if (yB + vy == y && xB + vx > x && xB + vx <= x + length / 2) {
        vy = -vy;
        vx = rand() % 3 - 1;

    } else if (yB + vy == y && xB + vx < x && xB + vx >= x - length / 2) {
        vy = -vy;
        vx = rand() % 3 - 1;

    }
}

inline void wall_collision() // wall colisions
{
    if ((yB + vy > height  && xB + vx == width) || (yB + vy > height  && xB + vx <= 0)) { // corner colision
        vy = -vy;
        vx = -vx;
    } else if (yB + vy > height) { // top wall colision
        vy = -vy;
    } else if (xB + vx >= width || xB + vx < 1) { // side walls
        vx = -vx;
    }
}

inline void brick_collision() // wall colisions
{
    if (bricks[yB + vy][xB] == 1) 
    {
        bricks[yB + vy][xB] = 0;
        vy = -vy;
    } else if (bricks[yB][xB + vx] == 1)
    {
        bricks[yB][xB + vx] = 0;
        vx = -vx;
    }
    else if (bricks[yB + vy][xB + vx] == 1)
    {
        bricks[yB + vy][xB + vx] = 0;
        vy = -vy;
        vx = -vx;
    }
}

inline void Logic() {
    yB += vy;
    xB += vx;

    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            if (y < 3) {
                y++;
            }
            break;
        case DOWN:
            if (y > 1) {
                y--;
            }
        case STOP:
            break;
        default:
            break;
    }

    // Check if the base goes out of bounds
    if (x >= width - length / 2 - 1) {
        x = width - length / 2 - 1;
    } else if (x <= length / 2 + 1) {
        x = length / 2 + 1;
    }

    wall_collision();
    paddle_collision();
    brick_collision();
    live_lost();
}

inline void initial_screen() // welcome screen and asks for the number of lives
{
    system("clear");
    while (true) {
        std::cout << "Small change2. Welcome to my paddle bounce game!! \n Provide the number of lives (must be 1 or greater): ";
        std::cin >> lives;

        // Check if the input is valid
        if (std::cin.fail() || lives < 1) {
            std::cin.clear(); // Clear the error flag set by invalid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
            std::cout << "Invalid input. Number of lives must be an integer and 1 or greater.\n";
        } else {
            break; // Break the loop if input is valid
        }
    }
}
#endif // FUNCTIONS_H
