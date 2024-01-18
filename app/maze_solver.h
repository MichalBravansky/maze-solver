enum tileType {path, wall};
typedef enum tileType tileType;

enum direction {left, up, right, down};
typedef enum direction direction;

struct Tile {
    enum tileType tileType;
    int visited;
};

struct Robot {
   int x;
   int y;
   enum direction direction;
};

struct Finish {
    int x;
    int y;
};


extern int width;
extern int height;

void printMaze(struct Tile map[][height], struct Robot *robot, struct Finish *finish);

void generateMaze(struct Tile map[][height], struct Robot *robot, struct Finish *finish);

void startProgram(struct Tile map[][height], struct Robot *robot, struct Finish *finish, int size);

void drawMap(struct Tile map[width][height], struct Finish *finish, int width, int height, int size);

void drawRobot(int x, int y, enum direction direct, int size);
void clearRobot(int x, int y, int size);
void drawEmptyPath(int x, int y, int size);
void drawSearchedPath(int x, int y, int size);
void drawFinish(int x, int y, int size);

void solveMaze(struct Tile map[width][height], struct Robot *robot, struct Finish *finish, int size, int wait_time);

void timeout(int millis);