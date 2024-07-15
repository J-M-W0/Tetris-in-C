#ifndef __TETRISDEF_H
#define __TETRISDEF_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

// Tetris type enumeration
enum TetrisType {
    TetrisTypeI = 0,
    TetrisTypeJ,
    TetrisTypeL,
    TetrisTypeO,
    TetrisTypeZ,
    TetrisTypeCount,
};
// Color enumeration
enum TetrisColor {
    TetrisColorRed = 0,
    TetrisColorGreen,
    TetrisColorBlue,
    TetrisColorBlack,
    TetrisColorCount,
};
enum TetrisDirection {
    TetrisDirectionUp = 0,
    TetrisDirectionRight,
    TetrisDirectionDown,
    TetrisDirectionLeft,
    TetrisDirectionCount,
};

// Each grid has its corresponding row and col number.
struct Grid {
    int row; // row index in gGrids, from 0.
    int col; // col index in gGrids, from 0.
};
// Each tetris consist of four grids.
struct Tetris {
    struct Grid grids[4];
    SDL_Color color;
    enum TetrisType type;
    enum TetrisDirection direction;
};

// Screen Width.
extern const int SCREEN_WIDTH;
// Screen Height.
extern const int SCREEN_HEIGHT;

// Left Coordinate of the Wall.
extern const int WALL_LEFT;
// Right Coordinate of the Wall.
extern const int WALL_RIGHT;
// The Bottom of the Wall.
extern const int WALL_BOTTOM;
// Thickness of the wall.
extern const int THICKNESS;

// Each grid is a square with height = width = GRID_SIZE.
extern const int GRID_SIZE;
// Total rows in the game grids.
extern const int GRID_ROWS;
// Total columns in the game grids.
extern const int GRID_COLS;
// Total count of the game grids.
extern const int GRID_COUNT;

// The falling speed of the tetris.
extern const int SPEED;

// The global Tetris (gTetris), each time only one tetris allowed to be created.
extern struct Tetris * gTetris;
// The global Count (gCount) of the already created tetris number.
extern int gCount;
// The global count for eliminated rows.
extern int gEliminatedRows;
// gGrids[row * GRID_COLS + col] = 
//      -1 - occupied by current tetris, 
//      0 - not occupied (white), 
//      >0 - occupied with color:
//          1 - red, 2 - green, 3 - blue, 4 - black
extern int * gGrids;

// Pointer to the window.
extern SDL_Window   * gWindow;
// Pointer to the renderer.
extern SDL_Renderer * gRenderer;
// Pointer to the font.
extern TTF_Font     * gFont;

// Constant Color Definitions:
extern const SDL_Color JUNZHE_red;
extern const SDL_Color JUNZHE_green;
extern const SDL_Color JUNZHE_blue;
extern const SDL_Color JUNZHE_black;
extern const SDL_Color JUNZHE_white;
extern const SDL_Color JUNZHE_lightgrey;
extern const SDL_Color JUNZHE_darkgrey;

#endif // __TETRISDEF_H
