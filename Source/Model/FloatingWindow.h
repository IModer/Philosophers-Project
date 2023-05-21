#ifndef _FLOATING_WINDOW_
#define _FLOATING_WINDOW_

#include "../Persistence/Field.h"
#include "../App/global.h"
#include "FireDepartment.h"
#include <raylib.h>

class GameModel;

class FloatingWindow 
{
    public:
    FloatingWindow(Field* field);

    bool IsMouseOver();
    void Render(GameModel* model);
    void RenderExtra();
    void OnClick(Vector2 pos);
    private:
    Field* _field;
    FireDepartment* fd;
    Rectangle rect;
    Rectangle fireRect;
};

#endif