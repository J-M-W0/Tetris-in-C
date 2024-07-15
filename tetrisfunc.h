#ifndef __TETRISFUNC_H
#define __TETRISFUNC_H
#include "gridfunc.h"

SDL_bool JUNZHE_checkTetrisCouldDraw(struct Tetris * tetris);
SDL_bool JUNZHE_drawTetris(struct Tetris * tetris);

SDL_bool JUNZHE_checkTetrisCouldMove(struct Tetris * tetris, SDL_bool leftOrRight);
SDL_bool JUNZHE_moveTetrisLeft(struct Tetris * tetris);
SDL_bool JUNZHE_moveTetrisRight(struct Tetris * tetris);

struct Tetris * JUNZHE_createTetris(int row, int col, enum TetrisType tetrisType);
struct Tetris * JUNZHE_createTetris2();
void JUNZHE_freeTetris(struct Tetris * tetris);

void JUNZHE_freezeTetris(struct Tetris * tetris);
struct Tetris * JUNZHE_updateTetris(struct Tetris * tetris);
SDL_bool JUNZHE_rotateTetris(struct Tetris * tetris);
void JUNZHE_dropDownTetris(struct Tetris * tetris);

#endif // __TETRISFUNC_H
