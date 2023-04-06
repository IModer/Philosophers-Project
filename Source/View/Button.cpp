#include "Button.h"
#include "View.h"
#include <raylib.h>

bool Button::isClicked()
{
    return View::isClickOnRect(_rect);
}

void Button::Render()
{
    DrawRectangleRec(_rect, isClicked()?BLUE:DARKBLUE);
    DrawText(_text.c_str(), _rect.x + (_rect.width - MeasureText(_text.c_str(), _fontSize)) / 2, _rect.y + (_rect.height - _fontSize) / 2, _fontSize, WHITE);
}