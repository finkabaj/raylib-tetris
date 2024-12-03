#ifndef HELPERS__
#define HELPERS__

#include "stdbool.h"
#include "types.h"

int max(int a, int b);
int min(int a, int b);

bool column_clear(int x, int from_y, int to_y);

Color get_color_from_shape(Shape shape);

void move_left();
void move_right();
void move_down();
void clear_tetro_from_field(Vector2 tetro[4]);
void place_tetro_on_field(Vector2 tetro[4], Shape shape);

#endif
