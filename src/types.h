#ifndef TYPES__
#define TYPES__

#include "raylib.h"

#define SCREEN_WIDTH 600
#define GAME_FIELD_WIDTH 400
#define SCREEN_HEIGHT 850
#define GAME_FIELD_HEIGHT 800
#define LINE_THICK 2
#define TICK 30
#define MAX_SPEED 25
#define ROWS 20
#define COLUMNS 10

typedef struct GameState GameState;

typedef struct Tetrimino Tetrimino;

typedef enum Shape Shape;

enum Shape
{
    STRAIGHT,
    SQUARE,
    LEFT,
    RIGHT,
    SKEW,
    T,
    SKEW_REVERSED,
};

struct Tetrimino
{
    int rotation;
    int cell;
    Shape shape;
    Color color;
};

struct GameState
{
    Tetrimino ***field;
    int speed;
    int score;
    int spawned;
    bool lost;
};

#endif
