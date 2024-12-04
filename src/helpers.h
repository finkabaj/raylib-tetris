#ifndef HELPERS__
#define HELPERS__

#include "stdbool.h"
#include "types.h"

int max(int a, int b);
int min(int a, int b);

Color get_color_from_shape(Shape shape);

bool has_hit();
void move_left();
void move_right();
void move_down();
void clear_tetro_from_field(Vector2 tetro[4]);
void place_tetro_on_field(Vector2 tetro[4], Shape shape);
bool spawn_clear(Vector2 tetro[4]);
void copy_new_pos_to_falling_piece(Vector2 new_pos[4]);

#endif
