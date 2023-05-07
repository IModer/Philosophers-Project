#include "FloatingWindow.h"
#include <raylib.h>


FloatingWindow::FloatingWindow(Field* field)
{
    _field = field;
    rect = Rectangle{static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()), static_cast<float>(MeasureText(_field->GetDescription().c_str(), 18)+12), 400};
}

/**
    *   \brief Renders a FloatingWindow object
    * 
    *   \return void
    **/
void FloatingWindow::Render()
{
    //Maybe we need checks if the render fails somewhere
    DrawRectangleRec(rect, Color{200, 200, 200, 200});
    DrawText(_field->GetDescription().c_str(), rect.x+6, rect.y+8, 18, WHITE);
}
