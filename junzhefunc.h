#ifndef __JUNZHEFUNC_H
#define __JUNZHEFUNC_H
#include "tetrisdef.h"
#include "gridfunc.h"
#include "tetrisfunc.h"

void JUNZHE_clearScreen(void);
void JUNZHE_clearRow(int row);
void JUNZHE_eliminateRow(int row);
void JUNZHE_checkUpdate(void);
void JUNZHE_drawWall(void);
SDL_bool JUNZHE_GameOver(void);

SDL_bool JUNZHE_loadFont( const char * fontname );
SDL_bool JUNZHE_init(void);
void JUNZHE_main(void);
void JUNZHE_close(void);


#endif // __JUNZHEFUNC_H
