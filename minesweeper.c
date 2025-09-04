#include <raylib.h>
#include <stdlib.h>
#include <raymath.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <sqlite3.h>
#include "headers/cells.h"

void Regen(void);
Game mainGame;
Grid grid;

int main(void)
{
    srand(time(NULL));
    InitWindow(WINWIDTH, WINHEIGHT, "Raylib app");

    Regen();

    InitAudioDevice();

    Sound boom = LoadSound("resources/boom.ogg");
    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ESCAPE))
            break;
        if (!mainGame.isOver & IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mPos = GetMousePosition();
            int indexI = mPos.x / CELLWIDTH;
            int indexJ = (mPos.y - HeightOff) / CELLHEIGHT;

            if (IndexisValid(indexI, indexJ))
            {

                grid[indexI][indexJ].clicked = true;
                if (grid[indexI][indexJ].isMined)
                {
                    PlaySound(boom);
                }
            }
        }

        BeginDrawing();
        ClearBackground((Color){20, 20, 20, 255});
        time_t timer = time(NULL) - mainGame.start_time;
        int minutes = (int)(timer / 60);
        time_t secs = timer % 60;

        DrawText("Man! Sweeper", WINWIDTH / 2 - MeasureText("Man! Sweeper", 50) / 2, HeightOff / 2 - 50 / 2, 50, (Color){255, 176, 38, 255});
        DrawText(TextFormat("Time: %02d:%02d", minutes, secs), 20, HeightOff - 40, 20, (Color){255, 176, 38, 255});

        for (int i = 0; i < COLS; i++)
        {
            for (int j = 0; j < ROWS; j++)
            {
                CellDraw(grid[i][j], &mainGame);
            }
        }

        if (mainGame.isOver)
        {
            DrawEndWindow(&mainGame, &Regen);
        }

        EndDrawing();
    }

    UnloadSound(boom);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

void Regen()
{
    mainGame = (Game){.isOver = false};

    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            grid[i][j] = (Cell){.i = i, .j = j, .clicked = false, .isMined = false, .neighbouringMines = -1};
        }
    }

    int nMines = (int)(COLS * ROWS * .1f);

    while (nMines > 0)
    {
        int i = rand() % COLS;
        int j = rand() % ROWS;

        if (!grid[i][j].isMined)
        {
            grid[i][j].isMined = true;
            nMines--;
        }
    }

    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            if (!grid[i][j].isMined)
            {

                grid[i][j].neighbouringMines = CellCountNMine(i, j, grid);
            }
        }
    }
    mainGame.start_time = time(NULL);
}
