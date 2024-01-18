#include "app/maze_solver.h"
#include <stdlib.h>

int areSettingsAllowed(int size, int wait_time){
    return (width >= 5) && (width <= 100) && (height >= 5) && (height <= 100) &&
            (size >=4) && (size <= 50) && (wait_time >= 0) && (width * size >= 50) &&
            (height * size >= 50) && (width*size <= 2500) && (height * size <= 1500);
}

int main(int argc, char **argv) {
    width = 100;
    height = 100;
    int size = 12;
    int wait_time = 50;
    int seed = 0;
    struct Finish finish;
    struct Robot robot;
    robot.direction = left;

    if (argc == 6){
        width = atoi(argv[1]);
        height = atoi(argv[2]);
        size = atoi(argv[3]);
        wait_time = atoi(argv[4]);
        seed = atoi(argv[5]);
    }

    if(!areSettingsAllowed(size, wait_time)){
        return 0;
    }

    srand(seed);

    struct Tile map[width][height];

    startProgram(map, &robot, &finish, size);

    solveMaze(map, &robot, &finish, size, wait_time);

    return 0;
}