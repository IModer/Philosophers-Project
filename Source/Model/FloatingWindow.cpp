#include "FloatingWindow.h"
#include <raylib.h>


FloatingWindow::FloatingWindow(Field* field)
{
    _pos = GetMousePosition();
    _field = field;
}

/**
    *   \brief Renders a FloatingWindow object
    * 
    *   \return void
    **/
void FloatingWindow::Render()
{
    //Maybe we need checks if the render fails somewhere
    DrawRectangleV(_pos, Vector2{200.f, 400.f}, GRAY);
    DrawText((BuildingNames.at(_field->GetId()) + "\nPosition: " + STR(_field->GetX()) + " " + STR(_field->GetY())).c_str(), _pos.x+4, _pos.y+8, 20, WHITE);
}