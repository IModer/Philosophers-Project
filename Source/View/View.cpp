#include "View.h"
#include <raylib.h>

bool View::isClickOnRect(Rectangle rect) {
    return GetMouseX() > rect.x && GetMouseX() < rect.x + rect.width && GetMouseY() > rect.y && GetMouseY() < rect.y + rect.height;
}

View::View(GameModel* model)
{
    _model = model;
    gameState = MENU;

    InitWindow(1920, 1080, "test");
    SetTargetFPS(60);

    newGameBtn = new Button("New Game", Rectangle{200, 200, 200, 40}, 20);
    loadGameBtn = new Button("Load Game", Rectangle{200, 300, 200, 40}, 20);
    exitBtn = new Button("Exit", Rectangle{200, 400, 200, 40}, 20);
};

void View::Update()
{
    // TODO: mouse, keyboard input, building, stb
    switch (gameState)
    {
        case MENU:
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        if (newGameBtn->isClicked()) {
            // TODO
        }
        if (loadGameBtn->isClicked()) {
            // TODO
        }
        if (exitBtn->isClicked()) {
            CloseWindow();
        }
        }
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

        newGameBtn->Render();
        loadGameBtn->Render();
        exitBtn->Render();
        
        EndDrawing();
        break;
        case GAME:
        for (Field* i : _model->_fields)
        {
            i->Render();
        }
        break;
    }
}