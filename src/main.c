#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "helpers.h"
#include "raylib.h"
#include "state.h"
#include "tetro.h"
#include "types.h"

void spawn()
{
    switch (rand() % 7)
    {
        case 0:
            return spawn_straight();
        case 1:
            return spawn_skew();
        case 2:
            return spawn_skew_reversed();
        case 3:
            return spawn_square();
        case 4:
            return spawn_t();
        case 5:
            return spawn_left();
        case 6:
            return spawn_right();
    }
}

void rotate()
{
    if (falling_piece.shape == SQUARE)
    {
        return;
    }

    clear_tetro_from_field(falling_piece.coords);

    float center_x = falling_piece.coords[0].x;
    float center_y = falling_piece.coords[0].y;

    Vector2 new_coords[4];
    new_coords[0] = falling_piece.coords[0];

    for (int i = 1; i < 4; i++)
    {
        float x = falling_piece.coords[i].x - center_x;
        float y = falling_piece.coords[i].y - center_y;

        float new_x = y;
        float new_y = -x;

        new_coords[i].x = new_x + center_x;
        new_coords[i].y = new_y + center_y;

        if (new_coords[i].x < 0 || new_coords[i].x > 9 || new_coords[i].y < 0 || new_coords[i].y > 19 ||
            game_state.field[(int)new_coords[i].y][(int)new_coords[i].x] != EMPTY)
        {
            return place_tetro_on_field(falling_piece.coords, falling_piece.shape);
        }
    }

    place_tetro_on_field(new_coords, falling_piece.shape);
    copy_new_pos_to_falling_piece(new_coords);
}

void delete_rows()
{
    int deleted_rows = 0;

    for (int y = 19; y >= 0; y--)
    {
        bool delete_row = true;
        for (int x = 0; x < 10; x++)
        {
            if (game_state.field[y][x] == EMPTY)
            {
                delete_row = false;
                break;
            }
        }

        if (delete_row)
        {
            for (int x = 0; x < 10; x++)
            {
                game_state.field[y][x] = EMPTY;
            }

            for (int yy = y - 1; yy >= 0; yy--)
            {
                for (int x = 0; x < 10; x++)
                {
                    game_state.field[yy + 1][x] = game_state.field[yy][x];
                }
            }

            deleted_rows++;
            y++;
        }
    }

    game_state.score += deleted_rows * 100;
}

void update_game()
{
    tick++;
    if (tick >= current_tick_rate)
    {
        if (has_hit())
        {
            game_state.score += 10;
            delete_rows();

            spawn();
        }
        else
        {
            move_down();
        }

        tick = 0;
    }
}

void draw_side_bar()
{
    Rectangle rec = {GAME_FIELD_WIDTH + 40, 0, SCREEN_WIDTH - GAME_FIELD_WIDTH - 20, SCREEN_HEIGHT};
    DrawRectangleRec(rec, GRAY);
    char score[100];
    sprintf(score, "SCORE:\n    %d", game_state.score);
    DrawText(score, (GAME_FIELD_WIDTH) + (SCREEN_WIDTH - GAME_FIELD_WIDTH - 20) / 2, 100, 20, GREEN);
}

void draw_game_field()
{
    Rectangle field_line = {20, 20, GAME_FIELD_WIDTH, GAME_FIELD_HEIGHT};

    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLUMNS; x++)
        {
            Rectangle cell = {20 + GAME_FIELD_WIDTH / 10.0f * x + LINE_THICK,
                              20 + GAME_FIELD_HEIGHT / 20.0f * y + LINE_THICK, GAME_FIELD_WIDTH / 10.0f - LINE_THICK,
                              GAME_FIELD_HEIGHT / 20.0f - LINE_THICK};
            Rectangle outline = {20 + GAME_FIELD_WIDTH / 10.0f * x, 20 + GAME_FIELD_HEIGHT / 20.0f * y,
                                 GAME_FIELD_WIDTH / 10.0f, GAME_FIELD_HEIGHT / 20.0f};

            Color cell_color = get_color_from_shape(game_state.field[y][x]);
            DrawRectangleRec(cell, cell_color);
            cell_color.r += 10;
            cell_color.g += 10;
            cell_color.b += 10;
            DrawRectangleLinesEx(cell, LINE_THICK, cell_color);
        }
    }

    DrawRectangleLinesEx(field_line, LINE_THICK, GRAY);
}

void draw_game()
{
    draw_side_bar();
    draw_game_field();
}

void process_input()
{
    if (game_state.lost)
    {
        if (GetKeyPressed() == KEY_SPACE)
        {
            init_game_state();
            spawn();
        }
        return;
    }

    switch (GetKeyPressed())
    {
        case KEY_LEFT:
            return move_left();
        case KEY_RIGHT:
            return move_right();
        case KEY_UP:
            return rotate();
    }

    if (IsKeyDown(KEY_DOWN))
    {
        current_tick_rate = FAST_TICK_RATE;
    }
    else
    {
        current_tick_rate = NORMAL_TICK_RATE;
    }
}

int main()
{
    srand(time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "tetris");

    SetTargetFPS(60);

    Image icon = LoadImage(ASSETS_PATH "icon.png");

    SetWindowIcon(icon);

    init_game_state();

    spawn();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground((Color){37, 37, 37, 0});

        draw_game();
        process_input();

        if (!game_state.lost)
        {
            update_game();
        }
        else
        {
            DrawText("YOU LOST!\nPRESS SPACE TO RESTART", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 20, 20, RED);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
