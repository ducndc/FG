#ifndef FLOPPY_UTILS_H
#define FLOPPY_UTILS_H

#define MAX_TUBES       100
#define FLOPPY_RADIUS   24
#define TUBES_WIDTH     80
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   450
#define FPS             60

typedef struct floppy_t {
    Vector2 position;
    int radius;
    Color color;
} floppy_t;

typedef struct tubes_t {
    Rectangle rec;
    Color color;
    bool active;
} tubes_t;

void init_game(void);

void update_game(void);

void draw_game(void);

void unload_game(void);

void update_draw_frame(void);

#endif