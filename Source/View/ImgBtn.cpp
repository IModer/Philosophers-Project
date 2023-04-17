#include "ImgBtn.h"
#include "View.h"
#include <raylib.h>

bool ImgBtn::isClicked()
{
    return GetMouseX() > _rect.x && GetMouseX() < _rect.x + _rect.width && GetMouseY() > _rect.y && GetMouseY() < _rect.y + _rect.height;
}

void ImgBtn::Render() 
{
    // render image
    DrawRectangleRec(_rect, isClicked()?GREEN:DARKGREEN);
    DrawText(_fName.c_str(), _rect.x + (_rect.width - MeasureText(_fName.c_str(), 18)) / 2, _rect.y + (_rect.height - 18) / 2, 18, WHITE);

    if (isClicked()) {
        if (hover > FPS) {
            DrawText(_helpText.c_str(), GetMouseX() + 10, GetMouseY() + 5,  16, GRAY);
        } else hover++;
    } else hover = 0;
}
