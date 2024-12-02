#include "helpers.h"

#include "state.h"

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

bool column_clear(int x, int from_y, int to_y)
{
    for (int y = from_y; y < to_y; y++)
    {
        if (game_state.field[y][x])
        {
            return false;
        }
    }

    return true;
}
