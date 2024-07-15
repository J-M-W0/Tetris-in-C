#ifndef __GRIDFUNC_H
#define __GRIDFUNC_H
#include "tetrisdef.h"

SDL_bool JUNZHE_initGrids();
void JUNZHE_freeGrids();

SDL_bool JUNZHE_checkGridCouldDraw(struct Grid * grid);
SDL_bool JUNZHE_checkGridCouldDraw2(int row, int col);
SDL_bool JUNZHE_ifValidGrid(struct Grid * grid);
SDL_bool JUNZHE_ifValidGrid2(int row, int col);

void JUNZHE_drawGrid(struct Grid * grid, SDL_Color * color);
void JUNZHE_renderGrids(int row, int col);


#endif // __GRIDFUNC_H
