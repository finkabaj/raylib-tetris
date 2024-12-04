#include "tetro.h"

#include "helpers.h"
#include "raylib.h"
#include "state.h"

void spawn_piece(Vector2 coords[4], Shape shape)
{
    if (!spawn_clear(coords))
    {
        game_state.lost = true;
    }

    falling_piece = (Tetrimino){T};
    for (int i = 0; i < 4; i++)
    {
        Vector2 pos = coords[i];
        falling_piece.coords[i] = pos;
        falling_piece.shape = shape;
        game_state.field[(int)pos.y][(int)pos.x] = shape;
    }
}

void spawn_t()
{
    Vector2 coords[4] = {{4, 0}, {3, 0}, {5, 0}, {4, 1}};
    spawn_piece(coords, T);
}

void spawn_straight()
{
    Vector2 coords[4] = {{4, 1}, {4, 0}, {4, 2}, {4, 3}};
    spawn_piece(coords, STRAIGHT);
}

void spawn_square()
{
    Vector2 coords[4] = {{4, 0}, {5, 0}, {4, 1}, {5, 1}};
    spawn_piece(coords, SQUARE);
}

void spawn_skew_reversed()
{
    Vector2 coords[4] = {{4, 0}, {3, 0}, {4, 1}, {5, 1}};
    spawn_piece(coords, SKEW_REVERSED);
}

void spawn_skew()
{
    Vector2 coords[4] = {{4, 0}, {5, 0}, {3, 1}, {4, 1}};
    spawn_piece(coords, SKEW);
}

void spawn_right()
{
    Vector2 coords[4] = {{4, 0}, {5, 0}, {5, 1}, {5, 2}};
    spawn_piece(coords, RIGHT);
}

void spawn_left()
{
    Vector2 coords[4] = {{5, 0}, {5, 1}, {5, 2}, {4, 2}};
    spawn_piece(coords, LEFT);
}
