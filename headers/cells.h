#ifndef cells
#define cells
#include <stdbool.h>
#include <time.h>

#define HeightOff 200

#define COLS 10
#define ROWS 10

#define WINWIDTH 600
#define WINHEIGHT 800

const int CELLWIDTH = WINWIDTH / COLS;
const int CELLHEIGHT = (WINHEIGHT - HeightOff) / ROWS;

typedef struct Cell
{
    int i;
    int j;
    bool clicked;
    bool isMined;
    int neighbouringMines;
} Cell;

typedef Cell Grid[100][280];

typedef struct Game
{
    Grid *grids;
    bool isOver;
    time_t start_time;
} Game;

void RevealCell(Cell cell, Game *game);
void CellDraw(Cell cell, Game *game);
int CellCountNMine(int i, int j, Grid grid);
bool IndexisValid(int i, int j);
void DrawEndWindow(Game *mainGame, void (*reset)(void));

#endif