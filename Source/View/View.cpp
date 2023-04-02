#include "View.h"

View::View(GameModel* model)
{
    _model = model;
    gameState = MENU;
};

void View::Update()
{
    // TODO: mouse, keyboard input, building, stb
    switch (gameState)
    {
        case MENU:

        break;
        case GAME:
        _model->Update();
        break;

    }

}

void View::Render()
{
    switch (gameState)
    {
        case MENU:

        break;
        case GAME:
        for (Field* i : _model->_fields)
        {
            i->Render(); //? mennyire szigorú a view-model?
        }
        break;
    }
}