#ifndef _TIME_BUTTON_
#define _TIME_BUTTON_

#include "../App/global.h"
#include "../Model/enum/time_enum.h"
#include <raylib.h>

class TimeButton {
    public:
    TimeButton(std::string text, TIME_ENUM time, Rectangle rect, std::string helpText) {
        txt = text;
        this->time = time;
        this->rect = rect;
        helpTxt = helpText;
    }
    TIME_ENUM getTime() { return time; }
    bool isClicked()
    {
        return GetMouseX() > rect.x && GetMouseX() < rect.x + rect.width && GetMouseY() > rect.y && GetMouseY() < rect.y + rect.height;
    }


    void Render(TIME_ENUM ct) {
        DrawRectangleRec(rect, isClicked()?GREEN:(ct==time?BLUE:DARKGREEN));
        DrawText(txt.c_str(), rect.x + (rect.width - MeasureText(txt.c_str(), 18)) / 2, rect.y + (rect.height - 18) / 2, 18, WHITE);
        if (isClicked()) {
            if (hover <= FPS)  hover++;
        } else hover = 0;
    }
    void RenderText() {
    if (hover > FPS) {
        DrawRectangle(GetMouseX()+ 12, GetMouseY() + 3, MeasureText(helpTxt.c_str(), 18) + 4, 22, Color{0, 0, 0, 200});
        DrawText(helpTxt.c_str(), GetMouseX() + 14, GetMouseY() + 5,  18, WHITE);
    }
}

    private:
    std::string txt;
    TIME_ENUM time;
    Rectangle rect;
    std::string helpTxt;
    int hover = 0;
};


#endif