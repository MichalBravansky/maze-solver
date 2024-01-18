enum tileType {path = 0, wall = 1};
enum direction {left = 0, up = 1, right = 2, down = 3};

struct Robot {
   int x;
   int y;
   enum direction direction;
};

struct Finish {
    int x;
    int y;
};

struct Tile {
    enum tileType tileType;
    int visited;
};