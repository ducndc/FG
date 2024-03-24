#include "raylib.h"
#include "floppy_utils.h"

const int g_screen_width = SCREEN_WIDTH;
const int g_screen_height = SCREEN_HEIGHT;

bool g_game_over = false;
bool g_pause = false;
int g_score = 0;
int g_high_score = 0;

floppy_t floppy = {0};
tubes_t g_tubes[MAX_TUBES * 2] = {0};
Vector2 g_tubes_position[MAX_TUBES] = {0};
int g_tubes_speed_x = 0;
bool g_super_fx = false;

void init_game(void)
{
    floppy.radius = FLOPPY_RADIUS;
    floppy.position = (Vector2){80, g_screen_height / 2 - floppy.radius};
    g_tubes_speed_x = 2;

    for (int i = 0; i < MAX_TUBES; ++i) {
        g_tubes_position[i].x = 400 + 280 * i;
        g_tubes_position[i].y = -GetRandomValue(0, 120);
    }

    for (int i = 0; i < MAX_TUBES * 2; i+= 2) {
        g_tubes[i].rec.x = g_tubes_position[i/2].x;
        g_tubes[i].rec.y = g_tubes_position[i/2].y;
        g_tubes[i].rec.width = TUBES_WIDTH;
        g_tubes[i].rec.height = 255;

        g_tubes[i+1].rec.x = g_tubes_position[i/2].x;
        g_tubes[i+1].rec.y = 600 + g_tubes_position[i/2].y - 255;
        g_tubes[i+1].rec.width = TUBES_WIDTH;
        g_tubes[i+1].rec.height = 255;

        g_tubes[i/2].active = true;
    }

    g_score = 0;

    g_game_over = false;
    g_super_fx = false;
    g_pause = false;
}

void update_game(void)
{
    if (!g_game_over) {
        if (IsKeyPressed('P')) 
            g_pause = !g_pause;
        if (!g_pause) {
            for (int i = 0; i < MAX_TUBES; ++i)
                g_tubes_position[i].x -= g_tubes_speed_x;
            for (int i = 0; i < MAX_TUBES * 2; i+= 2) {
                g_tubes[i].rec.x = g_tubes_position[i/2].x;
                g_tubes[i+1].rec.x = g_tubes_position[i/2].x;
            }

            if (IsKeyDown(KEY_SPACE) && !g_game_over)
                floppy.position.y -= 3;
            else
                floppy.position.y += 1;

            for (int i = 0; i < MAX_TUBES * 2; ++i) {
                if (CheckCollisionCircleRec(floppy.position, 
                                            floppy.radius, 
                                            g_tubes[i].rec)) {
                    g_game_over = true;
                    g_pause = false;
                } else if ((g_tubes_position[i/2].x < floppy.position.x) && 
                            g_tubes[i/2].active && !g_game_over) {
                    g_score += 100;
                    g_tubes[i/2].active = false;
                    g_super_fx = true;

                    if (g_score > g_high_score)
                        g_high_score = g_score;
                }
            }
        }
    } else {
        if (IsKeyPressed(KEY_ENTER)) {
            init_game();
            g_game_over = false;
        }
    }
}

void draw_game(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (!g_game_over) {
        DrawCircle(floppy.position.x, floppy.position.y, floppy.radius, RED);
        for (int i = 0; i < MAX_TUBES; ++i) {
            DrawRectangle(g_tubes[i * 2].rec.x, 
                          g_tubes[i * 2].rec.y, 
                          g_tubes[i * 2].rec.width, 
                          g_tubes[i * 2].rec.height, 
                          GREEN);
            DrawRectangle(g_tubes[i * 2 + 1].rec.x, 
                          g_tubes[i * 2 + 1].rec.y, 
                          g_tubes[i * 2 + 1].rec.width, 
                          g_tubes[i * 2 + 1].rec.height, 
                          GREEN);
        }

        if (g_super_fx) {
            DrawRectangle(0, 0, g_screen_width, g_screen_height, WHITE);
            g_super_fx = false;
        }

        DrawText(TextFormat("%04i", g_score), 20, 20, 40, BLACK);
        DrawText(TextFormat("HIGHEST SCORE: %04i", g_high_score), 20, 70, 20, BLACK);

        if (g_pause)
            DrawText("GAME PAUSED", 
                     g_screen_width / 2 - MeasureText("GAME PAUSED", 40) / 2, 
                     g_screen_height / 2 - 40, 
                     40, 
                     BLACK);
    } else {
        DrawText("PRESS [ENTER] TO PLAY AGAIN", 
                 GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, 
                 GetScreenHeight() / 2 - 50, 
                 20, 
                 BLACK);
    }

    EndDrawing();
}

void unload_game(void)
{
}

void update_draw_frame(void)
{
    update_game();
    draw_game();
}
