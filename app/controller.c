#include "maze_solver.h"
#include <stdlib.h>

int width;
int height;

void fillMaze(struct Tile map[width][height]){

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){

            map[x][y].tileType = wall;
            map[x][y].visited = 0;
        }
    }
}

int isTileSurroudedByPaths(struct Tile map[width][height], int x, int y){
    int is_path = 0;

    if(x-1>=0 && map[x-1][y].tileType == path){
        is_path+=1;
    }

    if(x+1< width && map[x+1][y].tileType == path){
        is_path+=1;
    }

    if(y-1>=0 && map[x][y-1].tileType == path){
        is_path+=1;
    }

    if(y+1<height && map[x][y+1].tileType == path){
        is_path+=1;
    }

    return is_path == 4;
}

void forward(struct Robot *robot){

    if(robot->direction == left){
        robot->x--;
    }
    else if(robot->direction == up){
        robot->y--;
    }
    else if(robot->direction == right){
        robot->x++;
    }
    else if(robot->direction == down){
        robot->y++;
    }
}

int canGoForward(struct Robot *robot, struct Tile map[width][height]){
    if(robot->direction == left){
        return (robot->x - 1 >= 0 && map[robot->x - 1][robot->y].tileType == path && !map[robot->x - 1][robot->y].visited);
    }
    else if(robot->direction == up){
        return (robot->y - 1 >= 0 && map[robot->x][robot->y - 1].tileType == path  && !map[robot->x][robot->y - 1].visited);
    }
    else if(robot->direction == right){
        return (robot->x + 1 < width && map[robot->x + 1][robot->y].tileType == path  && !map[robot->x + 1][robot->y].visited);
    }
    else if(robot->direction == down){
        return (robot->y + 1 < height && map[robot->x][robot->y + 1].tileType == path  && !map[robot->x][robot->y + 1].visited);
    }
}

// the function name was clashing with the value of the direction enum, therefore turnLeft() is used instead of just left()
void turnLeft(struct Robot *robot){
    if(robot->direction == left){
        robot->direction = down;
    }
    else if(robot->direction == down){
        robot->direction = right;
    }
    else if(robot->direction == right){
        robot->direction = up;
    }
    else if(robot->direction == up){
        robot->direction = left;
    }
}

void turnRight(struct Robot *robot){
    if(robot->direction == left){
        robot->direction = up;
    }
    else if(robot->direction == up){
        robot->direction = right;
    }
    else if(robot->direction == right){
        robot->direction = down;
    }
    else if(robot->direction == down){
        robot->direction = left;
    }
}

int atMarker(struct Robot *robot, struct Finish *finish){
    return (robot->x == finish->x) && (robot->y == finish->y);
}

int canMoveToTilePos(int x, int y, struct Tile map[width][height]){
    return (x >= 0) && (y >= 0) && (x < width) && (y < height) && !map[x][y].visited;
}

void moveBackWhileGenerating(int *pointer_x, int *pointer_y, struct Tile map[width][height]){
    int x = *pointer_x;
    int y= *pointer_y;
    int visited_count = map[x][y].visited;
    map[x][y].visited = -1;

    if((x-1 >= 0) && map[x-1][y].visited == visited_count - 1){
        x--;
    }
    else if((x+1 < width) && map[x+1][y].visited == visited_count - 1){
        x++;
    }
    else if((y-1>=0) && map[x][y - 1].visited == visited_count - 1){
        y--;
    }
    else if((y+1 < height) && map[x][y + 1].visited == visited_count - 1){
        y++;
    }

    *pointer_x = x;
    *pointer_y = y;
}

void tryToMoveWhileGenerating(int *pointer_x, int *pointer_y, int add_x, int add_y, struct Tile map[width][height]){
    int x = *pointer_x;
    int y = *pointer_y;

    map[x + add_x][y + add_y].visited = map[x][y].visited + 1;
    map[x + add_x][y + add_y].tileType = path;
    x+= add_x;
    y+= add_y;

    if(isTileSurroudedByPaths(map, x, y) || isTileSurroudedByPaths(map, x - 1, y) || isTileSurroudedByPaths(map, x, y - 1)||
    isTileSurroudedByPaths(map, x+1, y) || isTileSurroudedByPaths(map, x, y+1)){
        map[x][y].visited = -1;
        map[x][y].tileType = wall;
        x-= add_x;
        y-= add_y;
    }

    *pointer_x = x;
    *pointer_y = y;
}

void moveRandomDirectionWhileGenerating(int *x, int *y, int can_move_left, int can_move_up,
int can_move_right, int can_move_down, struct Tile map[width][height]){
    int direction = rand() % 4;

    if(direction==left && can_move_left){
        tryToMoveWhileGenerating(x, y, -1, 0, map);
    }
    else if(direction==up && can_move_up){
        tryToMoveWhileGenerating(x, y, 0, -1, map);
    }
    else if(direction== right && can_move_right){
        tryToMoveWhileGenerating(x, y, 1, 0, map);
    }
    else if(direction== down && can_move_down){
        tryToMoveWhileGenerating(x, y, 0, 1, map);
    }
}

// depth-first search generator, but modified so all empty tiles have a maximum of three empty neighbours
void generateMaze(struct Tile map[width][height], struct Robot *robot, struct Finish *finish){
    fillMaze(map);

    robot->x = rand() % width;
    robot->y = rand() % height;
    map[robot->x][robot->y].tileType = path;
    map[robot->x][robot->y].visited = 1;

    int x = robot->x;
    int y = robot->y;
    int finish_x = 0;
    int finish_y = 0;
    int max_visited = 0;

    for(int i = 0; i< (width * height); i++){

        int can_move_left = canMoveToTilePos(x - 1, y, map);
        int can_move_right = canMoveToTilePos(x + 1, y, map);
        int can_move_up = canMoveToTilePos(x, y - 1, map);
        int can_move_down = canMoveToTilePos(x, y + 1, map);

        if(!can_move_left && !can_move_right && !can_move_up && !can_move_down){
            moveBackWhileGenerating(&x, &y, map);
        }
        else{
            moveRandomDirectionWhileGenerating(&x, &y, can_move_left,
            can_move_up, can_move_right, can_move_down, map);

        if(map[x][y].visited > max_visited){
            finish_x = x;
            finish_y = y;
            max_visited = map[x][y].visited;
        }
        }
    }

    finish->x = finish_x;
    finish->y = finish_y;
}

void resetMetadata(struct Tile map[width][height]){
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            map[x][y].visited = 0;
        }
    }
}

void moveRobotToAdjectedTile(enum direction direct, struct Robot *robot, int size, int wait_time){
    while(robot->direction!=direct){
        turnLeft(robot);
        timeout(wait_time);
        drawRobot(robot->x, robot->y, robot->direction, size);
    }

    timeout(wait_time);
    drawEmptyPath(robot->x, robot->y, size);
    forward(robot);
    drawRobot(robot->x, robot->y, robot->direction, size);
}

int moveToUnvisitedTile(struct Tile map[width][height], struct Robot *robot, int size, int wait_time){
    for(int i = 0; i < 4; i++){
        if(canGoForward(robot, map)){

            timeout(wait_time);
            drawRobot(robot->x, robot->y, robot->direction, size);

            int visited_count = map[robot->x][robot->y].visited;
            timeout(wait_time);
            clearRobot(robot->x, robot->y, size);
            drawSearchedPath(robot->x, robot->y, size);

            forward(robot);
            drawRobot(robot->x, robot->y, robot->direction, size);

            map[robot->x][robot->y].visited = visited_count + 1;

            return 1;
        }
        
        turnRight(robot);
    }

    return 0;
}

void moveBackToVisitedTile(struct Tile map[width][height], struct Robot *robot, int size, int wait_time){
    int visited_count = map[robot->x][robot->y].visited;
    map[robot->x][robot->y].visited = -1;

    if(robot->x -1 >= 0 && map[robot->x - 1][robot->y].visited + 1 == visited_count){
        moveRobotToAdjectedTile(left, robot, size, wait_time);
    }
    else if(robot->y -1 >= 0 && map[robot->x][robot->y - 1].visited + 1 == visited_count){
        moveRobotToAdjectedTile(up, robot, size, wait_time);
    }
    else if(robot->x + 1 < width && map[robot->x + 1][robot->y].visited + 1 == visited_count){
        moveRobotToAdjectedTile(right, robot, size, wait_time);
    }
    else if(robot->y + 1 < height && map[robot->x][robot->y + 1].visited + 1 == visited_count){
        moveRobotToAdjectedTile(down, robot, size, wait_time);
    }

    timeout(wait_time);
}

void solveMaze(struct Tile map[width][height], struct Robot *robot, struct Finish *finish, int size, int wait_time){

    map[robot->x][robot->y].visited = 1;
    drawRobot(robot->x, robot->y, robot->direction, size);

    while(!atMarker(robot, finish)){

        if(!moveToUnvisitedTile(map, robot, size, wait_time)){
            moveBackToVisitedTile(map, robot, size, wait_time);
        }
    }
}


void startProgram(struct Tile map[width][height], struct Robot *robot, struct Finish *finish, int size){
    generateMaze(map, robot, finish);

    resetMetadata(map);

    drawMap(map, finish, width, height, size);
}
