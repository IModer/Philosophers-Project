#ifndef _BUTTON_
#define _BUTTON_

#include "../App/global.h"
#include <raylib.h>

class Button
{
    public:
    Button(std::string text, Rectangle rect, int fontSize) : _text(text), _rect(rect), _fontSize(fontSize) {};

    bool isClicked();

    void Render();
    private:
    std::string _text;
    Rectangle _rect;
    int _fontSize;
};

#endif