#ifndef _FLOATING_WINDOW_
#define _FLOATING_WINDOW_

#include "../Persistence/Field.h"
#include "../App/global.h"
#include <raylib.h>

class FloatingWindow 
{
    public:
    FloatingWindow(Field* field);

    void Update();
    void Render();
    void OnClick(INT_TOUPLE pos);
    private:
    Field* _field;
    Vector2 _pos;
};

#endif