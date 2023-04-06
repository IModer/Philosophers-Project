#include "View.h"
#include <raylib.h>
#include "rlgl.h"
#include "raymath.h"

bool View::isClickOnRect(Rectangle rect) {
    return GetMouseX() > rect.x && GetMouseX() < rect.x + rect.width && GetMouseY() > rect.y && GetMouseY() < rect.y + rect.height;
}

View::View(GameModel *model)
{
    _model = model;
    gameState = GAME;

    const int screenWidth = 1920;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "$[Game_name]");
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
        Camera2D camera = {0};
        camera.zoom = 1.0f;
        SetTargetFPS(60);

        while (!WindowShouldClose())
        {
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
        }
        CloseWindow();
        // for (Field *i : _model->_fields)
        // {
        //     i->Render(); //? mennyire szigorú a view-model?
        // }
        break;
    }
}