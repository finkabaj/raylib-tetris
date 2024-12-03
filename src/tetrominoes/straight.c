#include "straight.h"

#include "../state.h"
#include "raylib.h"

bool hit_straight()
{
    if (falling_piece.rotation % 2 == 0)
    {
        return falling_piece.top_y == 16 || game_state.field[falling_piece.top_y + 4][falling_piece.left_x] != EMPTY;
    }
    else
    {
        if (falling_piece.top_y == 19)
        {
            return true;
        }
        for (int x = falling_piece.left_x; x < falling_piece.left_x + 4; x++)
        {
            if (game_state.field[falling_piece.top_y][x] != EMPTY) return true;
        }
        return false;
    }
}

void rotate_straight() {}

void spawn_straight()
{
    Vector2 coords[4] = {{4, 0}, {4, 1}, {4, 2}, {4, 3}};
    falling_piece = (Tetrimino){0, STRAIGHT};
    for (int i = 0; i < 4; i++)
    {
        falling_piece.coords[i] = coords[i];
    }
    game_state.field[0][4] = STRAIGHT;
    game_state.field[1][4] = STRAIGHT;
    game_state.field[2][4] = STRAIGHT;
    game_state.field[3][4] = STRAIGHT;

    falling_piece.left_x = 4;
    falling_piece.top_y = 0;
}
