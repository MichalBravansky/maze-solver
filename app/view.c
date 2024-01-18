#include "../graphics.h"
#include "maze_solver.h"
#include <stdlib.h>

#define BORDER_DRAWING_THRESHOLD 10

void drawBorders(int x, int y, int size){
    if(BORDER_DRAWING_THRESHOLD <= size){
        setColour(gray);
        drawRect(x * size, y * size, size - 1, size - 1);
    }
}

void drawLeftRobot(int x, int y, int size){
    int points_x[3] = {x * size + size, x * size, x * size + size};
    int points_y[3] = {y * size, y * size + size / 2, y * size + size};
    fillPolygon(3, points_x, points_y);
}

void drawUpRobot(int x, int y, int size){
    int points_x[3] = {x * size, x * size + size / 2, x * size + size};
    int points_y[3] = {y * size + size, y * size, y * size + size};
    fillPolygon(3, points_x, points_y);
}

void drawRightRobot(int x, int y, int size){
    int points_x[3] = {x * size, x * size + size, x * size};
    int points_y[3] = {y * size, y * size + size / 2, y * size + size};
    fillPolygon(3, points_x, points_y);
}

void drawDownRobot(int x, int y, int size){
    int points_x[3] = {x * size, x * size + size / 2, x * size + size};
    int points_y[3] = {y * size, y * size + size, y * size};
    fillPolygon(3, points_x, points_y);
}

void drawRobot(int x, int y, enum direction direct, int size){
    setColour(white);
    fillRect(x * size, y * size, size, size);
    drawBorders(x, y, size);
    setColour(red);
    if(direct == left){
        drawLeftRobot(x, y, size);
    }
    else if(direct == up){
        drawUpRobot(x, y, size);
    }
    else if(direct == right){
        drawRightRobot(x, y, size);
    }
    else if(direct == down){
        drawDownRobot(x, y, size);
    }
}

void clearRobot(int x, int y, int size){
    setColour(white);
    fillRect(x * size, y * size, size, size);
}

void drawWall(int x, int y, int size){
    setColour(gray);
    fillRect(x * size, y * size, size, size);
}

void drawEmptyPath(int x, int y, int size){
    setColour(white);
    fillRect(x * size, y * size, size, size);
    drawBorders(x, y, size);
}

void drawSearchedPath(int x, int y, int size){
    setColour(yellow);
    fillRect(x * size, y * size, size, size);

    drawBorders(x, y, size);
}

void drawFinish(int x, int y, int size){
    setColour(black);
    fillRect(x * size, y * size, size, size);
}

void drawMap(struct Tile map[width][height], struct Finish *finish, int width, int height, int size){
    setWindowSize(size * width, size * height);
    background();

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){

            if(map[x][y].tileType == path){
                drawEmptyPath(x, y, size);
            }

            if(map[x][y].tileType == wall){
                drawWall(x, y, size);
            }
        }
    }

    drawFinish(finish->x, finish->y, size);

    foreground();
}

// this function allows the controller to access the sleep function without including the graphics library itself in controller
void timeout(int millis){
    sleep(millis);
}