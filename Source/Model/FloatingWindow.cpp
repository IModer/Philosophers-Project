#include "FloatingWindow.h"
#include "FireDepartment.h"
#include "GameField.h"
#include "GameModel.h"
#include "../View/View.h"
#include <cstddef>
#include <raylib.h>


FloatingWindow::FloatingWindow(Field* field)
{
    _field = field;
    rect = Rectangle{static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()), static_cast<float>(MeasureText(_field->GetDescription().c_str(), 24)+12), 400};
    fireRect = {rect.x+5, rect.y+rect.height-60, rect.width-10, 40};
}

bool FloatingWindow::IsMouseOver() {
    return View::isPosOnRect(GetMousePosition(), rect);
}

/**
    *   \brief Renders a FloatingWindow object
    * 
    *   \return void
    **/
void FloatingWindow::Render(GameModel* model)
{

    //Maybe we need checks if the render fails somewhere
    DrawRectangleRec(rect, Color{0, 0, 0, 200});
    DrawText(_field->GetDescription().c_str(), rect.x+6, rect.y+8, 24, WHITE);
    fd = nullptr;
    if (_field->GetId() != ROADANDELECTRICPOLE) {
        GameField* gf = (GameField*)_field;
        if (gf->IsOnFire()) {
            fd = model->GetClosestFireDepartment(_field);
            if (fd == nullptr) {
                DrawText("No fire departments nearby!", fireRect.x, fireRect.y, 20, RED);
            } else if (fd->getACount() > 0) {
                DrawText(("Firefighters available in: " + STR(fd->getACount()) + "s.").c_str(), fireRect.x, fireRect.y, 20, RED);
            } else {
                bool hover = View::isPosOnRect(GetMousePosition(), fireRect);
                DrawRectangleRec(fireRect, hover?WHITE:RED);
                DrawText("Send Firefighters", fireRect.x+20, fireRect.y+10, 20, hover?RED:WHITE);
            }
        }
    }

}

void FloatingWindow::RenderExtra() {
    // extra stuff
    if (_field->GetId() == FIREDEPARTMENT) {
        DrawRectangleRec(((FireDepartment*)_field)->GetRadiusRect(), {0, 255, 0, 100});
    }
}

void FloatingWindow::OnClick(Vector2 pos) {
    if (fd != nullptr) {
        ((GameField*)_field)->Extinguish();
        fd->Use();
    }
}
