#include "gridfunc.h"

SDL_bool JUNZHE_initGrids() {
    gGrids = (int*) malloc( GRID_COUNT * sizeof(int) );
    if ( !gGrids ) {
        return SDL_FALSE;
    }
    for (int i = 0; i < GRID_COUNT; i++) {
        gGrids[i] = 0;
    }
    return SDL_TRUE;
}

void JUNZHE_freeGrids() {
    if ( !gGrids ) {
        return;
    }
    free(gGrids);
}

// Called before @func {JUNZHE_drawGrid}, to check validity of the @param {grid}.
SDL_bool JUNZHE_checkGridCouldDraw(struct Grid * grid) {
    // Firstly, @param {grid} must be a valid pointer!
    if ( !grid ) {
        return SDL_FALSE;
    }
    // Secondly, @param {grid} must have valid row and col number.
    if (
        grid->row < 0 
        || grid->row >= GRID_ROWS
        || grid->col < 0
        || grid->col >= GRID_COLS
    ) 
    {
        return SDL_FALSE;
    }
    // Thirdly, the grid in @global {gGrids} must not be occupied.
    int index = grid->row * GRID_COLS + grid->col;
    if ( gGrids[index] > 0 ) {
        return SDL_FALSE;
    }
    // If all conditions satisfied, then return @const {SDL_TRUE},
    // otherwise return @const {SDL_FALSE}.
    return SDL_TRUE;
}
SDL_bool JUNZHE_checkGridCouldDraw2(int row, int col) {
    if (
        row < 0 
        || row >= GRID_ROWS
        || col < 0
        || col >= GRID_COLS
    ) 
    {
        return SDL_FALSE;
    }
    int index = row * GRID_COLS + col;
    if ( gGrids[index] > 0 ) {
        return SDL_FALSE;
    }
    return SDL_TRUE;
}

// Drawing the grid in the screen according to a Grid structure @param {grid} and @param {color}.
void JUNZHE_drawGrid(struct Grid * grid, SDL_Color * color) {
    // No need to check validity for the @var {row} and @var {col},
    // because they were already checked before drawing.
    int row = grid->row;
    int col = grid->col;
    // Getting the @var {index} of the @param {grid} in @global {gGrids}.
    int index = row * GRID_COLS + col;
    // -1 in @global {gGrids} means its occupied by current tetris,
    // so in the rendering process it will be treated differently.
    gGrids[index] = -1;

    // Getting the X- and Y-Coordinate of the @param {grid} in the screen.
    int x = GRID_SIZE * col + WALL_LEFT;
    int y = GRID_SIZE * row;
    // The Grid-Rectangle which will be rendered.
    SDL_Rect rect = {
        x, y,
        GRID_SIZE, GRID_SIZE
    };
    // Fill the Grid-Rectangle with the given @param {color}.
    SDL_SetRenderDrawColor( gRenderer, color->r, color->g, color->b, color->a );
    SDL_RenderFillRect( gRenderer, &rect );
    // Draw the outlines of the Grid-Rectangle with color black.
    SDL_SetRenderDrawColor( gRenderer, JUNZHE_black.r, JUNZHE_black.g, JUNZHE_black.b, JUNZHE_black.a );
    SDL_RenderDrawRect( gRenderer, &rect );
}

// Returns @const {SDL_TRUE} if the given @param {grid} is valid to be in the @global {gGrids}.
SDL_bool JUNZHE_ifValidGrid(struct Grid * grid) {
    int row = grid->row;
    int col = grid->col;
    if (row < 0 || row >= GRID_ROWS || col < 0 || col >= GRID_COLS) {
        return SDL_FALSE;
    }
    return SDL_TRUE;
}
// Returns @const {SDL_TRUE} if the given grid @param {row, col} is valid to be in the @global {gGrids}.
SDL_bool JUNZHE_ifValidGrid2(int row, int col) {
    if (row < 0 || row >= GRID_ROWS || col < 0 || col >= GRID_COLS) {
        return SDL_FALSE;
    }
    return SDL_TRUE;
}

void JUNZHE_renderGrids(int row, int col) {
    if (row < 0 || row >= GRID_ROWS || col < 0 || col >= GRID_COLS) {
        return;
    }
    int index = row * GRID_COLS + col;
    int x = col * GRID_SIZE + WALL_LEFT;
    int y = row * GRID_SIZE;
    SDL_Rect rect = {
        x, y,
        GRID_SIZE, GRID_SIZE
    };
    switch (gGrids[index]) {
        // Red
        case 1:
        {
            SDL_SetRenderDrawColor(gRenderer, JUNZHE_red.r, JUNZHE_red.g, JUNZHE_red.b, JUNZHE_red.a);
            SDL_RenderFillRect(gRenderer, &rect);
            // SDL_SetRenderDrawColor(gRenderer, JUNZHE_black.r, JUNZHE_black.g, JUNZHE_black.b, JUNZHE_black.a);
            SDL_SetRenderDrawColor( gRenderer, JUNZHE_white.r, JUNZHE_white.g, JUNZHE_white.b, JUNZHE_white.a );
            SDL_RenderDrawRect(gRenderer, &rect);
        } break;
        // Green
        case 2:
        {
            SDL_SetRenderDrawColor(gRenderer, 0, 0xff, 0, 0xff);
            SDL_RenderFillRect(gRenderer, &rect);
            SDL_SetRenderDrawColor( gRenderer, JUNZHE_white.r, JUNZHE_white.g, JUNZHE_white.b, JUNZHE_white.a );
            // SDL_SetRenderDrawColor(gRenderer, JUNZHE_black.r, JUNZHE_black.g, JUNZHE_black.b, JUNZHE_black.a);
            SDL_RenderDrawRect(gRenderer, &rect);
        } break;
        // Blue
        case 3:
        {
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0xff, 0xff);
            SDL_RenderFillRect(gRenderer, &rect);
            // SDL_SetRenderDrawColor(gRenderer, JUNZHE_black.r, JUNZHE_black.g, JUNZHE_black.b, JUNZHE_black.a);
            SDL_SetRenderDrawColor( gRenderer, JUNZHE_white.r, JUNZHE_white.g, JUNZHE_white.b, JUNZHE_white.a );
            SDL_RenderDrawRect(gRenderer, &rect);
        } break;
        // Black
        case 4:
        {
            SDL_SetRenderDrawColor( gRenderer, JUNZHE_black.r, JUNZHE_black.g, JUNZHE_black.b, JUNZHE_black.a );
            SDL_RenderFillRect(gRenderer, &rect);
            SDL_SetRenderDrawColor( gRenderer, JUNZHE_white.r, JUNZHE_white.g, JUNZHE_white.b, JUNZHE_white.a );
            SDL_RenderDrawRect(gRenderer, &rect);
        } break;
        // White
        case 0:
        {
            SDL_SetRenderDrawColor(gRenderer, JUNZHE_black.r, JUNZHE_black.g, JUNZHE_black.b, JUNZHE_black.a);
            SDL_RenderDrawRect(gRenderer, &rect);
        } break;

        // If -1 then don't execute any thing, it will be drawn another way.
        default: 
        {
        } break;
    }
}









