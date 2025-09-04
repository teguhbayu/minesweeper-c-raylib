#ifndef buttons
#define buttons
#include "cells.h"

typedef struct Button
{
    int height;
    int width;
    int winW;
    int winH;
    char text[20];
    void (*handler)(Game *, void (*reset)(void));
    Game *game;
    void (*reset)(void)
} Button;

void DrawButton(Button button);

#endif