#include "cells.h"
#include "buttons.h"
#include <raylib.h>
#include "utils.h"
#include <stdio.h>

bool IndexisValid(int i, int j)
{
    return i >= 0 && j >= 0 && i < COLS && j < ROWS;
}

void CellDraw(Cell cell, Game *game)
{
    int realI = cell.i * CELLWIDTH;
    int realJ = cell.j * CELLHEIGHT + HeightOff;
    if (cell.clicked)
    {
        RevealCell(cell, game);
    }
    DrawRectangleLines(realI, realJ, CELLWIDTH, CELLHEIGHT, (Color){120, 120, 120, 255});
}

void RevealCell(Cell cell, Game *game)
{
    int realI = cell.i * CELLWIDTH;
    int realJ = cell.j * CELLHEIGHT + HeightOff;
    if (cell.isMined)
    {
        DrawRectangle(realI, realJ, CELLWIDTH, CELLHEIGHT, (Color){225, 0, 100, 255});
        if (!game->isOver)
        {

            (*game).isOver = true;
        }
    }
    else
    {
        DrawRectangle(realI, realJ, CELLWIDTH, CELLHEIGHT, (Color){100, 0, 225, 255});
        DrawText(TextFormat("%d", cell.neighbouringMines), realI + (CELLWIDTH / 2 - MeasureText(TextFormat("%d", cell.neighbouringMines), 4) / 2), realJ + (CELLHEIGHT / 2 - 2), 4, (Color){225, 255, 255, 255});
    }
}

int CellCountNMine(int i, int j, Grid grid)
{
    int NMine = 0;
    for (int iOffs = -1; iOffs <= 1; iOffs++)
    {
        for (int jOffs = -1; jOffs <= 1; jOffs++)
        {
            if (IndexisValid(i + iOffs, j + jOffs) && grid[i + iOffs][j + jOffs].isMined)
            {
                NMine++;
            }
        }
    }

    return NMine;
}

void clickHandled(Game *mainGame, void (*reset)(void))
{
    (*reset)();
    (*mainGame).isOver = false;
}

void DrawEndWindow(Game *mainGame, void (*reset)(void))
{
    const int Winh = WINHEIGHT / 2;
    const int Winw = WINWIDTH / 1.5;

    Rectangle rect = {.height = Winh, .width = Winw, .x = WINWIDTH / 2 - Winw / 2, .y = WINHEIGHT / 2 - Winh / 2 + HeightOff / 2};

    Button button = {
        .height = 54,
        .width = 100,
        .text = "Ok",
        .winH = Winh,
        .winW = Winw,
        .handler = &clickHandled,
        .game = mainGame,
        .reset = reset};

    DrawRectangleRounded(rect, 0.05, 2, (Color){30, 30, 30, 255});
    DrawButton(button);
}