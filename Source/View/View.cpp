#include "View.h"
#include <raylib.h>
#include "rlgl.h"
#include "raymath.h"

bool View::isMouseOnRect(Rectangle rect) {
    // TODO
}

View::View(GameModel *model)
{
    _model = model;
    gameState = MENU;

    InitWindow(screenWidth, screenHeight, "$[Game_name]");

    newGameBtn = new Button("New game", Rectangle{screenWidth/2.f - 200, screenHeight/2.f, 400, 80}, 40);
    loadGameBtn = new Button("Load game", Rectangle{screenWidth/2.f - 200, screenHeight/2.f + 100, 400, 80}, 40);
    exitBtn = new Button("Exit game", Rectangle{screenWidth/2.f - 200, screenHeight/2.f + 200, 400, 80}, 40);

    camera = {0};
    camera.zoom = 1.0f;
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
            gameState = GAME;
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

        DrawText("$[game_name]", (screenWidth - MeasureText("$[game_name]", 60)) / 2, screenHeight/2 -80, 60, BLUE);

        newGameBtn->Render();
        loadGameBtn->Render();
        exitBtn->Render();
        
        EndDrawing();
        break;
    case GAME:
        SetTargetFPS(60);

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f / camera.zoom);

            camera.target = Vector2Add(camera.target, delta);
        }
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

            // Set the offset to where the mouse is
            camera.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point
            // under the cursor to the screen space point under the cursor at any zoom
            camera.target = mouseWorldPos;

            // Zoom increment
            const float zoomIncrement = 0.125f;

            camera.zoom += (wheel * zoomIncrement);
            if (camera.zoom < zoomIncrement)
                camera.zoom = zoomIncrement;
        }
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);

        // Draw the 3d grid, rotated 90 degrees and centered around 0,0
        // just so we have something in the XY plane
        rlPushMatrix();
        rlTranslatef(0, 25 * 50, 0);
        rlRotatef(90, 1, 0, 0);
        DrawGrid(100, 50);
        rlPopMatrix();

        // Draw a reference circle
        DrawCircle(100, 100, 50, YELLOW);

        EndMode2D();

        DrawText("Mouse right button drag to move, mouse wheel to zoom", 10, 10, 20, WHITE);

        EndDrawing();
        // for (Field *i : _model->_fields)
        // {
        //     i->Render(); //? mennyire szigorú a view-model?
        // }
        break;
    }
}