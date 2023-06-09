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
    protected:
    std::string _text;
    Rectangle _rect;
    int _fontSize;
};

class ExitButton : public Button {
    public:
    ExitButton(Rectangle rect) : Button("X", rect, 40) {};
    void Render();
};

class SaveButton : public Button {
    public:
    SaveButton(Rectangle rect, int n, bool available) : Button("Save file " + STR(n), rect, 40), _n(n), l(available) {};
    bool isClicked();
    void Render();
    void SetAvailable(bool w) {l = w;};
    private:
    int _n;
    bool l;
};

#endif