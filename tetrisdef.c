#include "tetrisdef.h"

// Screen Width.
const int SCREEN_WIDTH = 720;
// Screen Height.
const int SCREEN_HEIGHT = 720;

// Left Coordinate of the Wall.
const int WALL_LEFT = 60;
// Right Coordinate of the Wall.
const int WALL_RIGHT = SCREEN_WIDTH - 60;
// The Bottom of the Wall.
const int WALL_BOTTOM = SCREEN_HEIGHT - 30;
// Thickness of the wall.
const int THICKNESS = 15;

// Each grid is a square with height = width = GRID_SIZE.
const int GRID_SIZE = 30;
// Total rows in the game grids.
const int GRID_ROWS = (WALL_BOTTOM - 0) / GRID_SIZE;
// Total columns in the game grids.
const int GRID_COLS = (WALL_RIGHT - WALL_LEFT) / GRID_SIZE;
// Total count of the game grids.
const int GRID_COUNT = GRID_ROWS * GRID_COLS;

// The falling speed of the tetris.
const int SPEED = 200;

// The global Tetris (gTetris), each time only one tetris allowed to be created.
struct Tetris * gTetris = NULL;
// The global Count (gCount) of the already created tetris number.
int gCount = 0;
// The global count for eliminated rows.
int gEliminatedRows = 0;
// gGrids[row * GRID_COLS + col] = 
//      -1 - occupied by current tetris, 
//      0 - not occupied (white), 
//      >0 - occupied with color:
//          1 - red, 2 - green, 3 - blue, 4 - black
int * gGrids = NULL;

// Constant Color Definitions:
const SDL_Color JUNZHE_red = { 0xff, 0, 0, 0xff };
const SDL_Color JUNZHE_green = { 0, 0xff, 0, 0xff };
const SDL_Color JUNZHE_blue = { 0, 0, 0xff, 0xff };
const SDL_Color JUNZHE_black = { 0, 0, 0, 0xff };
const SDL_Color JUNZHE_white = { 0xff, 0xff, 0xff, 0xff };
const SDL_Color JUNZHE_lightgrey = { 200, 200, 200, 0xff };
const SDL_Color JUNZHE_darkgrey  = { 50, 50, 50, 0xff };

// Pointer to the window.
SDL_Window   * gWindow   = NULL;
// Pointer to the renderer.
SDL_Renderer * gRenderer = NULL;
// Pointer to the font.
TTF_Font     * gFont     = NULL;






