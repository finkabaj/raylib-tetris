#include "helpers.h"

#include "state.h"

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

bool column_clear(int x, int from_y, int to_y)
{
    for (int y = from_y; y < to_y; y++)
    {
        if (game_state.field[y][x] != EMPTY)
        {
            return false;
        }
    }

    return true;
}

Color get_color_from_shape(Shape shape)
{
    switch (shape)
    {
        case EMPTY:
            return BLACK;
        case STRAIGHT:
            return BLUE;
        case SKEW:
            return GREEN;
        case SKEW_REVERSED:
            return RED;
        case SQUARE:
            return YELLOW;
        case T:
            return PURPLE;
        case LEFT:
            return DARKBLUE;
        case RIGHT:
            return ORANGE;
    }
}

void clear_tetro_from_field(Vector2 tetro[4])
{
    for (int i = 0; i < 4; i++)
    {
        game_state.field[(int)tetro[i].y][(int)tetro[i].x] = EMPTY;
    }
}

void place_tetro_on_field(Vector2 tetro[4], Shape shape)
{
    for (int i = 0; i < 4; i++)
    {
        game_state.field[(int)tetro[i].y][(int)tetro[i].x] = shape;
    }
}

void copy_new_pos_to_falling_piece(Vector2 new_pos[4])
{
    for (int i = 0; i < 4; i++)
    {
        falling_piece.coords[i] = new_pos[i];
    }
}

void move_left()
{
    clear_tetro_from_field(falling_piece.coords);

    Vector2 new_cords[4];
    for (int i = 0; i < 4; i++)
    {
        new_cords[i].y = falling_piece.coords[i].y;
        new_cords[i].x = falling_piece.coords[i].x - 1;
        if ((int)falling_piece.coords[i].x - 1 < 0 ||
            game_state.field[(int)falling_piece.coords[i].y][(int)falling_piece.coords[i].x - 1] != EMPTY)
        {
            return place_tetro_on_field(falling_piece.coords, falling_piece.shape);
        }
    }

    place_tetro_on_field(new_cords, falling_piece.shape);
    copy_new_pos_to_falling_piece(new_cords);
    falling_piece.left_x--;
}

void move_right()
{
    clear_tetro_from_field(falling_piece.coords);

    Vector2 new_cords[4];
    for (int i = 0; i < 4; i++)
    {
        new_cords[i].y = falling_piece.coords[i].y;
        new_cords[i].x = falling_piece.coords[i].x + 1;
        if ((int)falling_piece.coords[i].x + 1 > 9 ||
            game_state.field[(int)falling_piece.coords[i].y][(int)falling_piece.coords[i].x + 1] != EMPTY)
        {
            return place_tetro_on_field(falling_piece.coords, falling_piece.shape);
        }
    }

    place_tetro_on_field(new_cords, falling_piece.shape);
    copy_new_pos_to_falling_piece(new_cords);
    falling_piece.left_x++;
}

void move_down()
{
    clear_tetro_from_field(falling_piece.coords);

    Vector2 new_cords[4];
    for (int i = 0; i < 4; i++)
    {
        new_cords[i].y = falling_piece.coords[i].y + 1;
        new_cords[i].x = falling_piece.coords[i].x;
        if ((int)falling_piece.coords[i].y + 1 > 19 ||
            game_state.field[(int)falling_piece.coords[i].y + 1][(int)falling_piece.coords[i].x] != EMPTY)
        {
            return place_tetro_on_field(falling_piece.coords, falling_piece.shape);
        }
    }

    place_tetro_on_field(new_cords, falling_piece.shape);
    copy_new_pos_to_falling_piece(new_cords);
    falling_piece.top_y++;
}
