#include "FloatingWindow.h"
#include "FireDepartment.h"
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

void FloatingWindow::RenderExtra() {
    // extra stuff
    if (_field->GetId() == FIREDEPARTMENT) {
        DrawRectangle(_field->GetX()-FireDepartment::radius*M_UNIT/2+M_UNIT, _field->GetY()-FireDepartment::radius*M_UNIT/2+M_UNIT, FireDepartment::radius*M_UNIT, FireDepartment::radius*M_UNIT, {0, 255, 0, 100});
    }
}
