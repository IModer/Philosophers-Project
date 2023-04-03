#include "View.h"
#include <raylib.h>

View::View(GameModel* model)
{
    _model = model;
    gameState = MENU;

    InitWindow(400, 400, "test");
    SetTargetFPS(60);
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
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
        break;
        case GAME:
        for (Field* i : _model->_fields)
        {
            i->Render(); //? mennyire szigorú a view-model?
        }
        break;
    }
}