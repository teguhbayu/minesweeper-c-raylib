#include "buttons.h"
#include <raylib.h>
#include <stdio.h>

void DrawButton(Button button)
{
    int x = WINWIDTH / 2 - button.winW / 2 + button.winW / 2 - button.width / 2;
    int y = WINHEIGHT / 2 - button.winH / 2 + HeightOff / 2 + button.winH - 80;

    Rectangle rect = {.height = button.height, .width = button.width, .x = x, .y = y};
    bool isHovered = CheckCollisionPointRec(GetMousePosition(), rect);

    if (isHovered)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            (*button.handler)(button.game, button.reset);
        }
    }
    DrawRectangleRounded(rect, 0.05, 2, isHovered ? (Color){125, 125, 125, 255} : (Color){255, 255, 255, 255});
    DrawText(button.text, x + button.width / 2 - MeasureText(button.text, 30) + 20, y + button.height / 2 - 13, 30, (Color){0, 0, 0, 255});
}