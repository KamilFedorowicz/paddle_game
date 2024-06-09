#include "functions.h"

// Define the variables declared as extern in the header
bool gameOver;
int x, y, xB, yB;
int vx, vy;
int length=7;
int lives;
int level=1;
int bricks[height][width];
eDirection dir;

void initialise_bricks() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i < (height - 2) && i > (height - 8) && j > (width / 2 - 3) && j < (width / 2 + 3)) {
                bricks[i][j] = rand() % 2;
            } else {
                bricks[i][j] = 0;
            }
        }
    }
}

int sum_bricks() {
    int sum = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            sum += bricks[i][j];
        }
    }
    return sum;
}

void initialise_ball() {
    vx = (rand() % 2 == 0) ? 1 : -1;
    vy = 1;
    xB = width / 2;
    yB = rand() % ((height - 1) / 2);
}

void Setup() {
    initialise_ball();
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = 1;
}

void Draw() {
    clear();
    printw("level  %d", level);
    printw("\n");
    for (int i = 0; i <= width; i++) {
        printw("#");
    }
    printw("\n");

    for (int i = height; i > 0; i--) {
        for (int j = 0; j <= width; j++) {
            if ((i == y) && (j <= x + length / 2) && (j >= x - length / 2)) {
                printw("=");
            } else if (j == 0 || j == width) {
                printw("#");
            } else if (bricks[i][j] == 1) {
                printw("o");
            } else if (i == yB && j == xB) {
                printw("O");
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }

    for (int i = 0; i <= width; i++) {
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

    refresh();
}

void Input() {
    nodelay(stdscr, TRUE);
    int ch = getch();
    if (ch != ERR) {
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
                dir = STOP;
                break;
        }
    } else {
        dir = STOP;
    }
}

void live_lost() {
    if (yB == 0) {
        lives--;
        if (lives <= 0) {
            gameOver = true;
        }
        initialise_ball();
    }
}

void paddle_collision() {
    if (yB + vy == y && (xB + vx == x || xB + vx == x + 1 || xB + vx == x - 1)) {
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

void wall_collision() {
    if ((yB + vy > height && xB + vx == width) || (yB + vy > height && xB + vx <= 0)) {
        vy = -vy;
        vx = -vx;
    } else if (yB + vy > height) {
        vy = -vy;
    } else if (xB + vx >= width || xB + vx < 1) {
        vx = -vx;
    }
}

void brick_collision() {
    if (bricks[yB + vy][xB] == 1) {
        bricks[yB + vy][xB] = 0;
        vy = -vy;
    } else if (bricks[yB][xB + vx] == 1) {
        bricks[yB][xB + vx] = 0;
        vx = -vx;
    } else if (bricks[yB + vy][xB + vx] == 1) {
        bricks[yB + vy][xB + vx] = 0;
        vy = -vy;
        vx = -vx;
    }
}

void Logic() {
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

void initial_screen() {
    system("clear");
    while (true) {
        std::cout << "Welcome to my paddle bounce game!! \n Provide the number of lives (must be 1 or greater): ";
        std::cin >> lives;

        if (std::cin.fail() || lives < 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Number of lives must be an integer and 1 or greater.\n";
        } else {
            break;
        }
    }
}
