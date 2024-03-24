/**
 *  Copyright (c) 2024 Chung Duc Nguyen Dang (David Nguyen)
 */

#include "raylib.h"
#include "floppy_utils.h"
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "floppy game");

    init_game();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(update_draw_frame, FPS, 1);
#else
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        update_draw_frame();
    }
#endif
    
    unload_game();

    CloseWindow();

    return 0;
}