#include "helpers.h"

#include "state.h"

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
}

bool has_hit()
{
    clear_tetro_from_field(falling_piece.coords);

    for (int i = 0; i < 4; i++)
    {
        Vector2 pos = falling_piece.coords[i];
        if (pos.y == 19 || game_state.field[(int)pos.y + 1][(int)pos.x] != EMPTY)
        {
            place_tetro_on_field(falling_piece.coords, falling_piece.shape);
            return true;
        }
    }

    place_tetro_on_field(falling_piece.coords, falling_piece.shape);

    return false;
}

bool spawn_clear(Vector2 tetro[4])
{
    for (int i = 0; i < 4; i++)
    {
        Vector2 pos = tetro[i];
        if (game_state.field[(int)pos.y][(int)pos.x] != EMPTY)
        {
            return false;
        }
    }

    return true;
}
