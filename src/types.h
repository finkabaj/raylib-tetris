#ifndef TYPES__
#define TYPES__

#include "raylib.h"

#define SCREEN_WIDTH 600
#define GAME_FIELD_WIDTH 400
#define SCREEN_HEIGHT 850
#define GAME_FIELD_HEIGHT 800
#define LINE_THICK 2
#define TICK 30
#define ROWS 20
#define COLUMNS 10

typedef enum Shape
{
    STRAIGHT,
    SQUARE,
    LEFT,
    RIGHT,
    SKEW,
    T,
    SKEW_REVERSED,
    EMPTY,
} Shape;

typedef struct Tetrimino
{
    int rotation;
    Shape shape;
    Vector2 coords[4];
    int left_x;
    int top_y;
} Tetrimino;

typedef struct GameState
{
    Shape field[20][10];
    int score;
    bool lost;
} GameState;

#endif
