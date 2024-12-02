#include "straight.h"

#include <stdlib.h>

#include "../helpers.h"
#include "../state.h"

void straight_fall()
{
    if (falling_piece->rotation % 2 == 0)
    {
        game_state.field[y_falling_piece][x_falling_piece] = NULL;
        game_state.field[y_falling_piece + 4][x_falling_piece] = falling_piece;
    }
    else
    {
        for (int x = x_falling_piece; x < COLUMNS; x++)
        {
            game_state.field[y_falling_piece][x_falling_piece] = NULL;
            game_state.field[y_falling_piece + 1][x_falling_piece] = falling_piece;
        }
    }
    y_falling_piece++;
}

bool hit_straight()
{
    if (falling_piece->rotation % 2 == 0)
    {
        return y_falling_piece == 16 || game_state.field[y_falling_piece + 4][x_falling_piece];
    }
    else
    {
        return y_falling_piece == 19 || game_state.field[y_falling_piece + 1];
    }
}

void spawn_straight()
{
    Tetrimino *straight = malloc(sizeof(Tetrimino));
    straight->color = BLUE;
    straight->cell = 4;
    straight->rotation = 0;
    straight->shape = STRAIGHT;
    game_state.field[0][4] = straight;
    game_state.field[1][4] = straight;
    game_state.field[2][4] = straight;
    game_state.field[3][4] = straight;

    falling_piece = straight;
    x_falling_piece = 4;
    y_falling_piece = 0;
}

void process_input_straight(int key)
{
    switch (key)
    {
        case KEY_LEFT:
            if (x_falling_piece - 1 < 0 || !column_clear(x_falling_piece - 1, y_falling_piece, y_falling_piece + 4))
            {
                return;
            }

            if (falling_piece->rotation % 2 == 0)
            {
                for (int y = y_falling_piece; y < y_falling_piece + 4; y++)
                {
                    game_state.field[y][x_falling_piece] = NULL;
                    game_state.field[y][x_falling_piece - 1] = falling_piece;
                }
            }
            else
            {
            }

            x_falling_piece--;
        case KEY_RIGHT:
        case KEY_UP:
        case KEY_DOWN:
    }
}
