#include "Button.h"
#include "View.h"
#include <raylib.h>

bool Button::isClicked()
{
    return GetMouseX() > _rect.x && GetMouseX() < _rect.x + _rect.width && GetMouseY() > _rect.y && GetMouseY() < _rect.y + _rect.height;
}


void Button::Render()
{
    DrawRectangleRec(_rect, isClicked()?BLUE:DARKBLUE);
    DrawText(_text.c_str(), _rect.x + (_rect.width - MeasureText(_text.c_str(), _fontSize)) / 2, _rect.y + (_rect.height - _fontSize) / 2, _fontSize, WHITE);
}

void ExitButton::Render() {
    DrawRectangleRec(_rect, isClicked()?Color{255, 100, 100, 255}:RED);
    DrawText(_text.c_str(), _rect.x + (_rect.width - MeasureText(_text.c_str(), _fontSize)) / 2, _rect.y + (_rect.height - _fontSize) / 2, _fontSize, WHITE);
}

bool SaveButton::isClicked() {
    return Button::isClicked() && l;
}

void SaveButton::Render() {
    if (l) {
        Button::Render();
    } else {
        DrawText("Empty File", _rect.x+(_rect.width-MeasureText("Empty File", 40))/2.f, _rect.y, 40, GRAY);
    }
}