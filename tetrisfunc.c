#include "tetrisfunc.h"
#include "gridfunc.h"
#include "tetrisdef.h"

// Check the validity of the @param {tetris}, called before @func {JUNZHE_drawTetris}.
SDL_bool JUNZHE_checkTetrisCouldDraw(struct Tetris * tetris) {
    // Firstly, the @param {tetris} pointer must be valid!
    if ( !tetris ) {
        return SDL_FALSE;
    }
    // Secondly, check for each member grid of the @param {tetris} for validity.
    for (int i = 0; i < 4; i++) {
        SDL_bool success = JUNZHE_checkGridCouldDraw(&tetris->grids[i]);
        // If any member grid failed to be valid, then return @const {SDL_FALSE},
        // which means the @param {tetris} cannot be drawn.
        if ( !success ) {
            return SDL_FALSE;
        }
    }
    // If all checks passed, then return @const {SDL_TRUE},
    // which means the @param {tetris} could be drawn.
    return SDL_TRUE;
}
// Draw the @param {tetris} onto the screen.
SDL_bool JUNZHE_drawTetris(struct Tetris * tetris) {
    // Checking validity.
    if ( !JUNZHE_checkTetrisCouldDraw(tetris) ) {
        // Failed to draw, return @const {SDL_FALSE}.
        return SDL_FALSE;
    }
    // Draw each member grid of the @param {tetris}.
    for (int i = 0; i < 4; i++) {
        JUNZHE_drawGrid(&tetris->grids[i], &tetris->color);
    }
    // 150ms delay for better looking.
    SDL_Delay( SPEED );
    // Successfully drawn, return @const {SDL_TRUE}.
    return SDL_TRUE;
}

// Check if could move @param {tetris} to the destinated position,
// @param {leftOrRight} determines which direction to move.
SDL_bool JUNZHE_checkTetrisCouldMove(struct Tetris * tetris, SDL_bool leftOrRight) {
    if (leftOrRight) {
        // SDL_TRUE for moving left,
        // each member grid moves one grid leftwards (grid.col -= 1).
        for (int i = 0; i < 4; i++) {
            int row = tetris->grids[i].row;
            int col = tetris->grids[i].col - 1;
            int index = row * GRID_COLS + col;
            if (col < 0 || gGrids[index] > 0) {
                return SDL_FALSE;
            }
        }
    } else {
        // SDL_FALSE for right,
        // each member grid moves one grid rightwards (grid.cal += 1).
        for (int i = 0; i < 4; i++) {
            int row = tetris->grids[i].row;
            int col = tetris->grids[i].col + 1;
            int index = row * GRID_COLS + col;
            if (col >= GRID_COLS || gGrids[index] > 0) {
                return SDL_FALSE;
            }
        }
    }
    return SDL_TRUE;
}

// Moving the @param {tetris} one grid leftwards.
SDL_bool JUNZHE_moveTetrisLeft(struct Tetris * tetris) {
    // Check for moving validity.
    if ( !JUNZHE_checkTetrisCouldMove(tetris, SDL_TRUE) ) {
        // Failed to draw.
        return SDL_FALSE;
    }
    for (int i = 0; i < 4; i++) {
        // Firstly clear the flag of the old position in @global {gGrids}.
        int index = tetris->grids[i].row * GRID_COLS + tetris->grids[i].col;
        gGrids[index] = 0;
    }
    for (int i = 0; i < 4; i++) {
        // Then update the new position,
        tetris->grids[i].col -= 1;
        // Draw the member grid.
        JUNZHE_drawGrid(&tetris->grids[i], &tetris->color);
    }
    // Successfully drawn.
    return SDL_TRUE;
}
// Moving the @param {tetris} one grid rightwards.
SDL_bool JUNZHE_moveTetrisRight(struct Tetris * tetris) {
    // Check for moving validity.
    if ( !JUNZHE_checkTetrisCouldMove(tetris, SDL_FALSE) ) {
        // Failed to draw.
        return SDL_FALSE;
    }
    for (int i = 0; i < 4; i++) {
        // Firstly clear the flag of the old position in @global {gGrids}.
        int index = tetris->grids[i].row * GRID_COLS + tetris->grids[i].col;
        gGrids[index] = 0;
    }
    for (int i = 0; i < 4; i++) {
        // Then update the new position,
        tetris->grids[i].col += 1;
        // Draw the member grid.
        JUNZHE_drawGrid(&tetris->grids[i], &tetris->color);
    }
    // Successfully drawn.
    return SDL_TRUE;
}

struct Tetris * JUNZHE_createTetris(int row, int col, enum TetrisType tetrisType) {
    struct Tetris * tetris = (struct Tetris*) malloc(sizeof(struct Tetris));
    if ( !tetris ) {
        fprintf (stderr, "Failed at JUNZHE_createTetris(): Not Enough Memory!!\n" );
        return NULL;
    }
    
    // Generate @var {colorType} in [0, 3]
    enum TetrisColor colorType = (enum TetrisColor) rand() % TetrisColorCount;
    SDL_Color color = JUNZHE_black;
    switch (colorType) {
        case TetrisColorRed:
        {
            color = JUNZHE_red;
        } break;

        case TetrisColorGreen:
        {
            color = JUNZHE_green;
        } break;

        case TetrisColorBlue:
        {
            color = JUNZHE_blue;
        } break;

        case TetrisColorBlack:
        {
            color = JUNZHE_black;
        } break;

        // Shouldn't be executed at all.
        default: 
        {
            fprintf (stderr, "Error: Bad TetrisColor!! %d\n", (int) colorType);
            JUNZHE_freeTetris(tetris);
            return NULL;
        } break;
    }
    tetris->color = color;

    switch (tetrisType) {
        // I-shape
        // [0]
        // [1]
        // [2]
        // [3]
        case TetrisTypeI:
        {
            tetris->grids[0] = (struct Grid) { row, col };
            tetris->grids[1] = (struct Grid) { row + 1, col };
            tetris->grids[2] = (struct Grid) { row + 2, col };
            tetris->grids[3] = (struct Grid) { row + 3, col };
        } break;

        // J-Shape
        //     [0]
        //     [1]
        // [3] [2]
        case TetrisTypeJ:
        {
            tetris->grids[0] = (struct Grid) { row, col };
            tetris->grids[1] = (struct Grid) { row + 1, col };
            tetris->grids[2] = (struct Grid) { row + 2, col };
            tetris->grids[3] = (struct Grid) { row + 2, col - 1 };
        } break;

        // L-Shape
        // [0]
        // [1]
        // [2] [3]
        case TetrisTypeL:
        {
            tetris->grids[0] = (struct Grid) { row, col };
            tetris->grids[1] = (struct Grid) { row + 1, col };
            tetris->grids[2] = (struct Grid) { row + 2, col };
            tetris->grids[3] = (struct Grid) { row + 2, col + 1 };
        } break;

        // O-shape
        // [0] [2]
        // [1] [3]
        case TetrisTypeO:
        {
            tetris->grids[0] = (struct Grid) { row, col };
            tetris->grids[1] = (struct Grid) { row + 1, col };
            tetris->grids[2] = (struct Grid) { row, col + 1 };
            tetris->grids[3] = (struct Grid) { row + 1, col + 1 };
        } break;
        
        // Z-Shape
        // [0] [1]
        //     [2] [3]
        case TetrisTypeZ:
        {
            tetris->grids[0] = (struct Grid) { row, col };
            tetris->grids[1] = (struct Grid) { row, col + 1 };
            tetris->grids[2] = (struct Grid) { row + 1, col + 1 };
            tetris->grids[3] = (struct Grid) { row + 1, col + 2 };
        } break;

        // Shouldn't be executing this.
        default:
        {
            fprintf (stderr, "Error: Bad TetrisType!!\n");
            JUNZHE_freeTetris(tetris);
            return NULL;
        } break;
    }
    tetris->type = tetrisType;
    tetris->direction = TetrisDirectionUp;

    gCount++;
    return tetris;
}

struct Tetris * JUNZHE_createTetris2() {
    int row = 0;
    int col;
    // Generate random number @var {tetrisType} in [0, 4]
    enum TetrisType tetrisType = (enum TetrisType) rand() % TetrisTypeCount;
    SDL_bool success = SDL_FALSE;
    do {
        // [0, GRID_COLS]
        col = rand() % (GRID_COLS + 1);
        // Firstly, the hot row and col must be valid.
        if (!JUNZHE_ifValidGrid2(row, col)) {
            continue;
        } 
        int row1;
        int col1;
        int row2;
        int col2;
        int row3;
        int col3;
        switch (tetrisType) {
            // I-shape
            // [*]
            // []
            // []
            // []
            case TetrisTypeI:
            {
                row1 = row + 1;
                col1 = col;
                row2 = row + 2;
                col2 = col;
                row3 = row + 3;
                col3 = col;
            } break;

            // J-Shape
            //    [*]
            //    []
            // [] []
            case TetrisTypeJ:
            {
                row1 = row + 1;
                col1 = col;
                row2 = row + 2;
                col2 = col;
                row3 = row + 2;
                col3 = col - 1;
            } break;

            // L-Shape
            // [*]
            // []
            // [] []
            case TetrisTypeL:
            {
                row1 = row + 1;
                col1 = col;
                row2 = row + 2;
                col2 = col;
                row3 = row + 2;
                col3 = col + 1;
            } break;

            // O-shape
            // [*] []
            // []  []
            case TetrisTypeO:
            {
                row1 = row + 1;
                col1 = col;
                row2 = row;
                col2 = col + 1;
                row3 = row + 1;
                col3 = col + 1;
            } break;
            
            // Z-Shape
            // [*] []
            //     [] []
            case TetrisTypeZ:
            {
                row1 = row;
                col1 = col + 1;
                row2 = row + 1;
                col2 = col + 1;
                row3 = row + 1;
                col3 = col + 2;
            } break;

            // Shouldn't be executing this.
            default:
            {
                fprintf (stderr, "Error: Bad TetrisType!!\n");
                return NULL;
            } break;
        }

        // Then also check for other grids for validity.
        if (
            !JUNZHE_ifValidGrid2(row1, col1)
            || !JUNZHE_ifValidGrid2(row2, col2)
            || !JUNZHE_ifValidGrid2(row3, col3)
        ) 
        {
            continue;
        }

        // If every test passes, then go for creating it.
        success = SDL_TRUE;
    } while ( !success );

    return JUNZHE_createTetris(row, col, tetrisType);
}

void JUNZHE_freeTetris(struct Tetris * tetris) {
    if ( !tetris ) {
        return;
    }
    free(tetris);
}

void JUNZHE_freezeTetris(struct Tetris * tetris) {
    SDL_Color color = tetris->color;
    int colorCode = 0;
    if (color.r == 0xff && color.g == 0 && color.b == 0) {
        colorCode = 1; // red
    } else if (color.r == 0 && color.g == 0xff && color.b == 0) {
        colorCode = 2; // green
    } else if (color.r == 0 && color.g == 0 && color.b == 0xff) {
        colorCode = 3; // blue
    } else if (color.r == 0 && color.g == 0 && color.b == 0) {
        colorCode = 4; // black
    }
    for (int i = 0; i < 4; i++) {
        int row = tetris->grids[i].row;
        int col = tetris->grids[i].col;
        int index = row * GRID_COLS + col;
        gGrids[index] = colorCode;
    }
}

// Draw the tetris on the screen, then update it's next (falling down) position.
struct Tetris * JUNZHE_updateTetris(struct Tetris * tetris) {
    if ( !tetris ) {
        return NULL;
    }
    // Firstly, draw the current tetris.
    JUNZHE_drawTetris(tetris);
    // Secondly, check if the tetris is valid for next draw. (falling down)
    // If not, then freeze the tetris.
    for (int i = 0; i < 4; i++) {
        int row = tetris->grids[i].row + 1;
        int col = tetris->grids[i].col;
        SDL_bool success = JUNZHE_checkGridCouldDraw2(row, col);
        if ( !success ) {
            JUNZHE_freezeTetris(tetris);
            JUNZHE_freeTetris(tetris);
            return NULL;
        }
    }
    for (int i = 0; i < 4; i++) {
        int oldIndex = tetris->grids[i].row * GRID_COLS + tetris->grids[i].col;
        gGrids[oldIndex] = 0;
        tetris->grids[i].row += 1;
    }
    // Returns NULL if tetris is frozen, otherwise the updated tetris pointer.
    return tetris;
}

SDL_bool JUNZHE_rotateTetris(struct Tetris * tetris) {
    if ( !tetris ) {
        return SDL_FALSE;
    }

    struct Grid grids[4];
    int row = tetris->grids[0].row;
    int col = tetris->grids[0].col;
    switch (tetris->type) {
        case TetrisTypeI:
        {
            /* Let's consider that I-shaped tetris has only two forms of rotation.
            UP:
                [0]
                [1]
                [2]
                [3]
            DOWN:
                [0] [1] [2] [3]
            * */
            if (tetris->direction == TetrisDirectionUp) {
                // From UP convert to DOWN.
                grids[0] = (struct Grid) { row, col };
                grids[1] = (struct Grid) { row, col + 1 };
                grids[2] = (struct Grid) { row, col + 2 };
                grids[3] = (struct Grid) { row, col + 3 };
                for (int i = 0; i < 4; i++) {
                    if ( !JUNZHE_checkGridCouldDraw(&grids[i]) ) {
                        return SDL_FALSE;
                    }
                }
                tetris->direction = TetrisDirectionDown;
            } else {
                // From DOWN convert to UP.
                grids[0] = (struct Grid) { row, col };
                grids[1] = (struct Grid) { row + 1, col };
                grids[2] = (struct Grid) { row + 2, col };
                grids[3] = (struct Grid) { row + 3, col };
                for (int i = 0; i < 4; i++) {
                    if ( !JUNZHE_checkGridCouldDraw(&grids[i]) ) {
                        return SDL_FALSE;
                    }
                }
                tetris->direction = TetrisDirectionUp;
            }
        } break;
        
        case TetrisTypeJ:
        {
            /*
            UP:
                    [0]
                    [1]
                [3] [2]
            RIGHT:
                [3]
                [2] [1] [0]
            DOWN:
                [2] [3]
                [1]
                [0]
            LEFT:
                [0] [1] [2]
                        [3]
            * */
            switch (tetris->direction) {
                case TetrisDirectionUp:
                {
                    // UP -> RIGHT
                    grids[0] = (struct Grid) { row + 2, col + 1 };
                    grids[1] = (struct Grid) { row + 2, col};
                    grids[2] = (struct Grid) { row + 2, col - 1 };
                    grids[3] = (struct Grid) { row + 1, col - 1 };
                    for (int i = 0; i < 4; i++) {
                        if ( !JUNZHE_checkGridCouldDraw(&grids[i]) ) {
                            return SDL_FALSE;
                        }
                    }
                    tetris->direction = ((tetris->direction) + 1) % TetrisDirectionCount;
                } break;

                case TetrisDirectionRight:
                {
                    // RIGHT -> DOWN
                    grids[0] = (struct Grid) { row + 1, col - 2 };
                    grids[1] = (struct Grid) { row, col - 2 };
                    grids[2] = (struct Grid) { row - 1, col - 2 };
                    grids[3] = (struct Grid) { row - 1, col - 1 };
                    for (int i = 0; i < 4; i++) {
                        if ( !JUNZHE_checkGridCouldDraw(&grids[i]) ) {
                            return SDL_FALSE;
                        }
                    }
                    tetris->direction = ((tetris->direction) + 1) % TetrisDirectionCount;
                } break;

                case TetrisDirectionDown:
                {
                    // DOWN -> LEFT
                    grids[0] = (struct Grid) { row - 2, col };
                    grids[1] = (struct Grid) { row - 2, col + 1 };
                    grids[2] = (struct Grid) { row - 2, col + 2 };
                    grids[3] = (struct Grid) { row - 1, col + 2 };
                    for (int i = 0; i < 4; i++) {
                        if ( !JUNZHE_checkGridCouldDraw(&grids[i]) ) {
                            return SDL_FALSE;
                        }
                    }
                    tetris->direction = ((tetris->direction) + 1) % TetrisDirectionCount;
                } break;

                case TetrisDirectionLeft:
                { 
                    // LEFT -> UP
                    grids[0] = (struct Grid) { row - 2, col + 1};
                    grids[1] = (struct Grid) { row - 1, col + 1 };
                    grids[2] = (struct Grid) { row, col + 1 };
                    grids[3] = (struct Grid) { row, col };
                    for (int i = 0; i < 4; i++) {
                        if ( !JUNZHE_checkGridCouldDraw(&grids[i]) ) {
                            return SDL_FALSE;
                        }
                    }
                    tetris->direction = ((tetris->direction) + 1) % TetrisDirectionCount;
                } break;

                // Should've never exeuted this.
                default: {} break;
            }
        } break;

        case TetrisTypeL:
        {
            /*
            UP:
                [0]
                [1]
                [2] [3]
            RIGHT:
                [2] [1] [0]
                [3]
            DOWN:
                [3] [2]
                    [1]
                    [0]
            LEFT:
                        [3]
                [0] [1] [2]
            * */
            switch (tetris->direction) {
                case TetrisDirectionUp:
                {
                    // UP -> RIGHT
                    grids[0] = (struct Grid) { row, col + 2 };
                    grids[1] = (struct Grid) { row, col + 1 };
                    grids[2] = (struct Grid) { row, col };
                    grids[3] = (struct Grid) { row + 1, col };
                    for (int i = 0; i < 4; i++) {
                        if ( !JUNZHE_checkGridCouldDraw(&grids[i]) ) {
                            return SDL_FALSE;
                        }
                    }
                    tetris->direction = ((tetris->direction) + 1) % TetrisDirectionCount;
                } break;

                case TetrisDirectionRight:
                {
                    // RIGHT -> DOWN
                    grids[0] = (struct Grid) { row, col };
                    grids[1] = (struct Grid) { row - 1, col };
                    grids[2] = (struct Grid) { row - 2, col };
                    grids[3] = (struct Grid) { row - 2, col - 1 };
                    for (int i = 0; i < 4; i++) {
                        if ( !JUNZHE_checkGridCouldDraw(&grids[i]) ) {
                            return SDL_FALSE;
                        }
                    }
                    tetris->direction = ((tetris->direction) + 1) % TetrisDirectionCount;
                } break;

                case TetrisDirectionDown:
                {
                    // DOWN -> LEFT
                    grids[0] = (struct Grid) { row, col - 1 };
                    grids[1] = (struct Grid) { row, col };
                    grids[2] = (struct Grid) { row, col + 1 };
                    grids[3] = (struct Grid) { row - 1, col + 1 };
                    for (int i = 0; i < 4; i++) {
                        if ( !JUNZHE_checkGridCouldDraw(&grids[i]) ) {
                            return SDL_FALSE;
                        }
                    }
                    tetris->direction = ((tetris->direction) + 1) % TetrisDirectionCount;
                } break;

                case TetrisDirectionLeft:
                {
                    // LEFT -> UP
                    grids[0] = (struct Grid) { row - 2, col };
                    grids[1] = (struct Grid) { row - 1, col };
                    grids[2] = (struct Grid) { row, col };
                    grids[3] = (struct Grid) { row, col + 1 };
                    for (int i = 0; i < 4; i++) {
                        if ( !JUNZHE_checkGridCouldDraw(&grids[i]) ) {
                            return SDL_FALSE;
                        }
                    }
                    tetris->direction = ((tetris->direction) + 1) % TetrisDirectionCount;
                } break;

                // Should've never exeuted this.
                default: {} break;
            }
        } break;

        case TetrisTypeO:
        {
            // Let's consider that O-shaped tetris cannot rotate.
            return SDL_FALSE;
        } break;

        case TetrisTypeZ:
        {
            /* Let's consider that Z-Shaped tetris has only two forms of rotation.
            UP:
                [0] [1]
                    [2] [3]
            DOWN:
                    [0]
                [2] [1] 
                [3]
            * */
            if (tetris->direction == TetrisDirectionUp) {
                // UP -> DOWN
                grids[0] = (struct Grid) { row, col + 1};
                grids[1] = (struct Grid) { row + 1, col + 1 };
                grids[2] = (struct Grid) { row + 1, col };
                grids[3] = (struct Grid) { row + 2, col };
                for (int i = 0; i < 4; i++) {
                    if ( !JUNZHE_checkGridCouldDraw(&grids[i]) ) {
                        return SDL_FALSE;
                    }
                }
                tetris->direction = TetrisDirectionDown;
            } else {
                // DOWN -> UP
                grids[0] = (struct Grid) { row, col - 1 };
                grids[1] = (struct Grid) { row, col };
                grids[2] = (struct Grid) { row + 1, col };
                grids[3] = (struct Grid) { row + 1, col + 1 };
                for (int i = 0; i < 4; i++) {
                    if ( !JUNZHE_checkGridCouldDraw(&grids[i]) ) {
                        return SDL_FALSE;
                    }
                }
                tetris->direction = TetrisDirectionUp;
            }
        } break;

        // Shouldn't have ever exeuted here.
        default: { } break;
    }

    for (int i = 0; i < 4; i++) {
        if ( !JUNZHE_checkGridCouldDraw(&grids[i]) ) {
            return SDL_FALSE;
        }
    }

    for (int i = 0; i < 4; i++) {
        int index = tetris->grids[i].row * GRID_COLS + tetris->grids[i].col;
        gGrids[index] = 0;
    }
    for (int i = 0; i < 4; i++) {
        JUNZHE_drawGrid(&grids[i], &tetris->color);
        tetris->grids[i] = grids[i];
    }

    return SDL_TRUE;
}

void JUNZHE_dropDownTetris(struct Tetris * tetris) {
    struct Grid grids[4];
    while (1) {
        for (int i = 0; i < 4; i++) {
            grids[i] = tetris->grids[i];
            grids[i].row += 1;
            if ( !JUNZHE_checkGridCouldDraw(&grids[i]) ) {
                return;
            }
        }
        for (int i = 0; i < 4; i++) {
            int index = tetris->grids[i].row * GRID_COLS + tetris->grids[i].col;
            gGrids[index] = 0;
        }
        for (int i = 0; i < 4; i++) {
            tetris->grids[i] = grids[i];
            JUNZHE_drawGrid(&tetris->grids[i], &tetris->color);
        }
    }
}
