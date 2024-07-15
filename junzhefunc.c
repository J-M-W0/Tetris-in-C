#include "junzhefunc.h"
#include "tetrisdef.h"
#include "tetrisfunc.h"

// Clear the whole screen, paint it white.
void JUNZHE_clearScreen() {
    SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xff );
    SDL_RenderClear( gRenderer );
}

// Clear the whole @param {row}, making their corresponding values all to @const {0}.
void JUNZHE_clearRow(int row) {
    for (int j = 0; j < GRID_COLS; j++) {
        int index = row * GRID_COLS + j;
        gGrids[index] = 0;
    }
}
// Eliminate one @param {row}, making every row above one grid downwards.
void JUNZHE_eliminateRow(int row) {
    if (row == 0) {
        // If the top row to be eliminated. Then just clear the row.
        JUNZHE_clearRow(row);
    } else {
        // If not the top row, then firstly clear the row.
        // Then move each row above one grid downwards.
        JUNZHE_clearRow(row);
        for (int i = row - 1; i >= 0; i--) {
            for (int j = 0; j < GRID_COLS; j++) {
                if (i == 0) {
                    // If it's the 0-th row, then simply clear the row.
                    JUNZHE_clearRow(i);
                    continue;
                }
                // Moving the rows one grid below.
                int index = i * GRID_COLS + j;
                int indexBelow = index + GRID_COLS;
                gGrids[indexBelow] = gGrids[index];
            }
        }
    }
}

void JUNZHE_checkUpdate() {
    int occupiedCount;
    for (int i = 0; i < GRID_ROWS; i++) {
        occupiedCount = 0;
        for (int j = 0; j < GRID_COLS; j++) {
            int index = i * GRID_COLS + j;
            if (gGrids[index] > 0) {
                occupiedCount++;
            }
        }
        // If one whole row is totally occupied, then eliminate one row.
        if (occupiedCount == GRID_COLS) {
            gEliminatedRows++;
            JUNZHE_eliminateRow(i);
        }
    }
}

void JUNZHE_drawWall() {
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xff);
    for (int i = 0; i < THICKNESS; i++) {
        SDL_RenderDrawLine(
            gRenderer,
            WALL_LEFT - i, 0,
            WALL_LEFT - i, SCREEN_HEIGHT
        );
        SDL_RenderDrawLine(
            gRenderer,
            WALL_RIGHT + i, 0,
            WALL_RIGHT + i, SCREEN_HEIGHT
        );
    }
    for (int i = 0; i < 30; i++) {
        SDL_RenderDrawLine(
            gRenderer,
            WALL_LEFT, WALL_BOTTOM + i,
            WALL_RIGHT, WALL_BOTTOM + i
        );
    }
    JUNZHE_checkUpdate();
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            JUNZHE_renderGrids(i, j);
        }
    }
}

SDL_bool JUNZHE_GameOver() {
    for (int i = 0; i < 4; i++) {
        int row = gTetris->grids[i].row;
        int col = gTetris->grids[i].col;
        int index = row * GRID_COLS + col;
        if (gGrids[index] > 0) {
            return SDL_TRUE;
        }
    }

    for (int i = 0; i < 4; i++) {
        JUNZHE_drawGrid(&gTetris->grids[i], &gTetris->color);
    }
    
    return SDL_FALSE;
}

SDL_bool JUNZHE_loadFont( const char * fontname ) {
    if ( !fontname ) {
        return SDL_FALSE;
    }
    gFont = TTF_OpenFont( fontname, 20 );
    if ( !gFont ) 
    {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Failed at TTF_OpenFont(%s) :%s\n", fontname, TTF_GetError() );
        return SDL_FALSE;
    }
    return SDL_TRUE;
}

SDL_bool JUNZHE_init() {
    if ( SDL_Init(SDL_INIT_VIDEO 
                | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Failed at SDL_Init(): %s\n", SDL_GetError() );
        return SDL_FALSE;
    }
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "VIDEO subsystem initialized.\n" );
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "AUDIO subsystem initialized.\n" );
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "TIMER subsystem initialized.\n" );

    if ( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") ) {
        SDL_LogWarn( SDL_LOG_CATEGORY_APPLICATION, "Failed at SDL_SetHint(): %s\n", SDL_GetError() );
    }

    gWindow = SDL_CreateWindow(
        "Tetris - Developed by Wang, Junzhe",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN 
        // | SDL_WINDOW_RESIZABLE
    );
    if ( !gWindow ) {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Failed at SDL_CreateWindow(): %s\n", SDL_GetError() );
        SDL_Quit();
        return SDL_FALSE;
    }
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "WINDOW initialized.\n" );

    gRenderer = SDL_CreateRenderer(
        gWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if ( !gRenderer ) {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Failed at SDL_CreateRenderer(): %s\n", SDL_GetError() );
        SDL_DestroyWindow( gWindow );
        gWindow = NULL;
        SDL_Quit();
        return SDL_FALSE;
    }
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "RENDER initialized.\n" );

    SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xff );
    SDL_RenderClear( gRenderer );

    int imgFlags = IMG_INIT_PNG;
    int initFlags = IMG_Init( imgFlags );
    if ( imgFlags != (initFlags & imgFlags) ) {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Failed at IMG_Init(): %s\n", IMG_GetError() );
        SDL_DestroyRenderer( gRenderer );
        gRenderer = NULL;
        SDL_DestroyWindow( gWindow );
        gWindow = NULL;
        SDL_Quit();
        return SDL_FALSE;
    }
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "IMG subsytem initialized.\n" );

    if ( TTF_Init() == -1 ) {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Failed at TTF_Init(): %s\n", TTF_GetError() );
        SDL_DestroyRenderer( gRenderer );
        gRenderer = NULL;
        SDL_DestroyWindow( gWindow );
        gWindow = NULL;
        gRenderer = NULL;
        IMG_Quit();
        SDL_Quit();
        return SDL_FALSE;
    }
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "TTF subsytem initialized.\n" );

    /*
    char fontPath[1024];
    bzero(fontPath, sizeof(fontPath));
    snprintf(fontPath, sizeof(fontPath), "OpenSans-Regular.ttf");
    if ( !JUNZHE_loadFont( fontPath ) ) {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Failed at load_font()\n" );
        SDL_DestroyWindow( gWindow );
        gWindow = NULL;
        SDL_DestroyRenderer( gRenderer );
        gRenderer = NULL;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return SDL_FALSE;
    }
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "OpenSans-Regular.ttf font loaded.\n" );
    */
    
    SDL_StartTextInput();
    return SDL_TRUE;
}

void JUNZHE_main() {
    SDL_bool  done = SDL_FALSE;
    SDL_bool  success;
    SDL_bool  GameOver = SDL_FALSE;
    SDL_Event event;
    do {
        while ( SDL_PollEvent(&event) ) 
        {
            if (event.type == SDL_QUIT) {
                done = SDL_TRUE;
            }
            // If a key was pressed.
            else if (event.type == SDL_KEYDOWN && event.key.repeat == 0 ) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                    {
                        // Try to rotate clockwise the @global {gTetris}.
                        success = JUNZHE_rotateTetris(gTetris);
                        if ( !success ) {
                            printf("\a");
                        }
                    } break;

                    case SDLK_DOWN:
                    {
                        // Try to immediately smash the @global {gTetris} down to the bottom.
                        JUNZHE_dropDownTetris(gTetris);
                    } break;

                    case SDLK_LEFT:
                    {
                        // Try to move the @global {gTetris} leftwards.
                        success = JUNZHE_moveTetrisLeft(gTetris);
                        if ( !success ) {
                            // If failed to move, ring a bell.
                            printf("\a");
                        }
                    } break;

                    case SDLK_RIGHT: 
                    {
                        // Try to move the @global {gTetris} rightwards.
                        success = JUNZHE_moveTetrisRight(gTetris);
                        if ( !success ) {
                            // If failed to move, ring a bell.
                            printf("\a");
                        }
                    } break;
                }
            } // END key pressed.
        } // END while ( SDL_PollEvent(&event) )
        JUNZHE_clearScreen();

        if ( !GameOver ) {
            gTetris = JUNZHE_updateTetris(gTetris);
            while ( !gTetris ) {
                gTetris = JUNZHE_createTetris2();
                GameOver = JUNZHE_GameOver();
            }
        }

        JUNZHE_drawWall();
        SDL_RenderPresent( gRenderer );
    } while ( !done );

    JUNZHE_freeTetris( gTetris );

    printf("Total tetris generated: [%d]\n", gCount);
    printf("Total rows eliminated:  [%d]\n", gEliminatedRows);

    JUNZHE_freeGrids();
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Grids have been freed!!\n" );
}

void JUNZHE_close() {
    SDL_StopTextInput();
    
    TTF_CloseFont( gFont );
    gFont = NULL;
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "OpenSans-Regular.ttf font closed.\n" );
    
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "RENDER destroyed.\n" );
    
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "WINDOW destroyed.\n" );
    
    TTF_Quit();
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "TTF subsytem quited.\n" );
    
    IMG_Quit();
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "IMG subsytem quited.\n" );
    
    SDL_Quit();
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "TIMER subsytem initialized.\n" );
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "AUDIO subsytem initialized.\n" );
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "VIDEO subsytem initialized.\n" );
}






