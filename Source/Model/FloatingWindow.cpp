#include "FloatingWindow.h"
#include <raylib.h>

FloatingWindow::FloatingWindow(Field* field)
{
    _pos = GetMousePosition();
    _field = field;
}

void FloatingWindow::Render()
{
    DrawRectangleV(_pos, Vector2{200, 400}, GRAY);
    DrawText("No Name\nDisplaying data", _pos.x+4, _pos.y+8, 20, WHITE);
}