#include "tetrisdef.h"
#include "gridfunc.h"
#include "tetrisfunc.h"
#include "junzhefunc.h"

int main(int argc, char * argv[]) {
    if ( !JUNZHE_init() ) {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Error: Failed at init()\n" );
        return -1;
    }
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Initialization finished!!\n" );

    // Initialize random seed.
    srand(time(NULL));
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Random seed initialized!!\n" );

    if ( !JUNZHE_initGrids() ) {
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Error: Failed at JUNZHE_initGrids()\n" );
        JUNZHE_close();
        return -1;
    }

    gTetris = JUNZHE_createTetris2();
    if ( !gTetris ) {
        JUNZHE_close();
        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Error: Failed to initialize a begin tetris!!\n" );
        return -1;
    }

    JUNZHE_main();

    JUNZHE_close();
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Program finished!!\n" );
    return 0;
}
