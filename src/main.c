#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "helpers.h"
#include "raylib.h"
#include "state.h"
#include "tetrominoes/left.h"
#include "tetrominoes/right.h"
#include "tetrominoes/skew.h"
#include "tetrominoes/skew_reversed.h"
#include "tetrominoes/square.h"
#include "tetrominoes/straight.h"
#include "tetrominoes/t.h"
#include "types.h"

bool hit()
{
    switch (falling_piece.shape)
    {
        case STRAIGHT:
            return hit_straight();
        case SQUARE:
            return hit_square();
        case LEFT:
            return hit_left();
        case RIGHT:
            return hit_right();
        case SKEW:
            return hit_skew();
        case T:
            return hit_t();
        case SKEW_REVERSED:
            return hit_skew_reversed();
        default:
            return false;
    }
}

void spawn()
{
    spawn_straight();
    // switch (rand() % 7)
    //{
    //     case 0:
    //         return spawn_straight();
    //     case 1:
    //         return spawn_skew();
    //     case 2:
    //         return spawn_skew_reversed();
    //     case 3:
    //         return spawn_square();
    //     case 4:
    //         return spawn_t();
    //     case 5:
    //         return spawn_left();
    //     case 6:
    //         return spawn_right();
    // }
}

void rotate()
{
    switch (falling_piece.shape)
    {
        case STRAIGHT:
            return rotate_straight();
        case LEFT:
            return rotate_left();
        case RIGHT:
            return rotate_right();
        case SKEW:
            return rotate_skew();
        case T:
            return rotate_t();
        case SKEW_REVERSED:
            return rotate_skew_reversed();
        default:
            return;
    }
}

void delete_rows() {}

void update_game()
{
    if (hit())
    {
        delete_rows();

        spawn();

        return;
    }

    move_down();
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
    switch (GetKeyPressed())
    {
        case KEY_LEFT:
            return move_left();
        case KEY_RIGHT:
            return move_right();
        case KEY_DOWN:
            return move_down();
        case KEY_UP:
            return rotate();
    }
}

int main()
{
    srand(time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "tetris");
    SetWindowState(FLAG_VSYNC_HINT);

    if (!IsWindowState(FLAG_VSYNC_HINT))
    {
        SetTargetFPS(60);
    }

    Image icon = LoadImage(ASSETS_PATH "icon.png");

    SetWindowIcon(icon);

    init_game_state();

    spawn();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground((Color){37, 37, 37, 0});

        if (!game_state.lost)
        {
            process_input();

            tick++;
            if (tick % TICK == 0)
            {
                update_game();
                draw_game();
            }
        }
        else
        {
            DrawText("YOU LOST!", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 20, 20, RED);
        }

        draw_game();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
