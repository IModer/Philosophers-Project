#ifndef _FLOATING_WINDOW_
#define _FLOATING_WINDOW_

#include "../Persistence/field.h"
#include "../App/global.h"

class FloatingWindow 
{
    public:
    FloatingWindow(Field* field);

    void Update();
    void Render();
    void OnClick(INT_TOUPLE pos);
    private:
    Field _filed;
};

#endif