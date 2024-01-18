# COMP0002 Principles of Programming 

## Description
The presented program generates a random maze and then lets a robot solve it. The robot (red triangle) uses depth-first search to find its way to the finish tile (black tile). User is able modify the program behavior, such as the size of the maze, the speed of the robot and the seed of the maze.

## Project structure
The project consists of a main.c file and a folder called app. Within this folder, there are three .c files, view.c, controller.c and model.c, each corresponding to the model-view-controller (MVC) architecture. As such, only the view.c file has access to the graphics library.

## How to run
First, copy all the files from the drawing app into the main folder containing main.c. Then, compile the program with the following command:
gcc -o main main.c graphics.c app/view.c app/controller.c app/model.c  -lm

Afterwards, you should see an executable in the main folder. You can test the program with:
Windows: ./main.exe | java -jar drawapp-2.0.jar
Linux / Mac: ./main.out | java -jar drawapp-2.0.jar

You can also pass custom arguments to the executed program. Use the following structure:
Windows: ./main.exe WIDTH HEIGHT PIXEL_SIZE WAIT_TIME SEED | java -jar drawapp-2.0.jar
Linux / Mac: ./main.out WIDTH HEIGHT PIXEL_SIZE WAIT_TIME SEED | java -jar drawapp-2.0.jar

As an example, run this command on your machine:
Windows: ./main.exe 100 60 6 10 42 | java -jar drawapp-2.0.jar
Linux / Mac: ./main.out 100 60 6 10 42 | java -jar drawapp-2.0.jar

## Argument description
WIDTH – the width of the maze, integer from 5 to 100
HEIGHT – the height of the maze, integer from 5 to 100
PIXEL_SIZE – the pixel size of one tile, integer from 4 to 50
WAIT_TIME – the waiting time between each step of the robot, positive integer
SEED – the seed for the maze generation, integer