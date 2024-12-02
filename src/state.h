#ifndef STATE__
#define STATE__

#include "types.h"

extern GameState game_state;
extern int tick;

extern Tetrimino *falling_piece;
extern int x_falling_piece;
extern int y_falling_piece;

void init_game_state();

#endif
