#include "state.h"

GameState game_state;
int tick;
int current_tick_rate;

Tetrimino falling_piece;
int x_falling_piece;
int y_falling_piece;

void init_game_state()
{
    game_state.lost = false;
    game_state.score = 0;

    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            game_state.field[y][x] = EMPTY;
        }
    }
}
