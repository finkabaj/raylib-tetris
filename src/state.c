#include "state.h"

#include <stdlib.h>

GameState game_state;
int tick;

Tetrimino *falling_piece;
int x_falling_piece;
int y_falling_piece;

void init_game_state()
{
    game_state.lost = false;
    game_state.speed = 0;
    game_state.score = 0;
    game_state.spawned = 0;

    game_state.field = malloc(ROWS * sizeof(Tetrimino **));

    if (!game_state.field)
    {
        TraceLog(LOG_FATAL, "error mallocating field.");
        exit(1);
    }

    for (int y = 0; y < 20; y++)
    {
        game_state.field[y] = malloc(COLUMNS * sizeof(Tetrimino *));

        if (!game_state.field[y])
        {
            TraceLog(LOG_FATAL, "error mallocating field.");
            exit(1);
        }

        for (int x = 0; x < 10; x++)
        {
            game_state.field[y][x] = NULL;
        }
    }
}
