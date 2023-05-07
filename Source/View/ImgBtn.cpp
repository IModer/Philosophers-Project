#include "ImgBtn.h"
#include "View.h"
#include <raylib.h>

bool ImgBtn::isClicked()
{
    return GetMouseX() > _rect.x && GetMouseX() < _rect.x + _rect.width && GetMouseY() > _rect.y && GetMouseY() < _rect.y + _rect.height;
}

void ImgBtn::Render(bool active) 
{
    // render image
    DrawRectangleRec(_rect, isClicked()?GREEN:(active?BLUE:DARKGREEN));
    DrawText(_fName.c_str(), _rect.x + (_rect.width - MeasureText(_fName.c_str(), 18)) / 2, _rect.y + (_rect.height - 18) / 2, 18, WHITE);

    if (isClicked()) {
        if (hover <= FPS)  hover++;
    } else hover = 0;
}

void ImgBtn::RenderText() {
    if (hover > FPS) {
        DrawRectangle(GetMouseX()+ 12, GetMouseY() + 3, MeasureText(_helpText.c_str(), 18) + 4, 22, Color{0, 0, 0, 200});
        DrawText(_helpText.c_str(), GetMouseX() + 14, GetMouseY() + 5,  18, WHITE);
    }
}
