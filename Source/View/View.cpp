#include "View.h"
#include "ImgBtn.h"
#include "rlgl.h"
#include "raymath.h"
#include "../Model/FloatingWindow.h"
#include <cstdio>
#include <raylib.h>

bool View::isPosOnRect(Vector2 Pos, Rectangle rect)
{
    return Pos.x > rect.x && Pos.x < rect.x + rect.width && Pos.y > rect.y && Pos.y < rect.y + rect.height;
}

View::View(GameModel *model)
{
    _model = model;
    gameState = MENU;

    InitWindow(screenWidth, screenHeight, "$[Game_name]");
    SetWindowState(FLAG_FULLSCREEN_MODE);

    /* Menu buttons */
    newGameBtn = new Button("New game", Rectangle{screenWidth / 2.f - 200, screenHeight / 2.f, 400, 80}, 40);
    loadGameBtn = new Button("Load game", Rectangle{screenWidth / 2.f - 200, screenHeight / 2.f + 100, 400, 80}, 40);
    exitBtn = new Button("Exit game", Rectangle{screenWidth / 2.f - 200, screenHeight / 2.f + 200, 400, 80}, 40);

    /* Action Buttons */
    actionButtons[0] = new ImgBtn("Road", ROADANDELECTRICPOLE, Rectangle{ 10, 60, 130, 130 }, "Makes a rectangle"); 
    actionButtons[1] = new ImgBtn("Residential", RESIDENTALZONE, Rectangle{ 160, 60, 130, 130 }, "Makes a rectangle"); 
    actionButtons[2] = new ImgBtn("Forest", FOREST, Rectangle{ 10, 210, 130, 130 }, "Makes a rectangle"); 
    actionButtons[3] = new ImgBtn("Fire department", FIREDEPARTMENT, Rectangle{ 160, 210, 130, 130 }, "Makes a rect"); 
    actionButtons[4] = new ImgBtn("Bontás", DEMOLISH, Rectangle{ 160, 360, 130, 130 }, "Deletes a rectangle"); 

    camera = {0};
    camera.zoom = 1.0f;

    SetTargetFPS(60);
};

void View::Update()
{
    // TODO: mouse, keyboard input, building, stb
    switch (gameState)
    {
    case MENU:
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (newGameBtn->isClicked())
            {
                // TODO
                gameState = GAME;
                _model->NewGame();
            }
            if (loadGameBtn->isClicked())
            {
                // TODO
            }
            if (exitBtn->isClicked())
            {
                CloseWindow();
            }
        }
        break;
    case GAME:
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

                    // Round the position to the nearest multiple of 50
        int gridX = static_cast<int>(mouseWorldPos.x / 50) * 50;
        if(mouseWorldPos.x < 0.0)
        {
            printf("insideif\n");
            gridX -= 50;
        }
        int gridY = static_cast<int>(mouseWorldPos.y / 50) * 50; // ez jó
        if(mouseWorldPos.y < 0.0)
        {
            printf("insideif\n");
            gridY = gridY -50;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f / camera.zoom);

            camera.target = Vector2Add(camera.target, delta);
        }
        //left click
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            bool l = true;
            if (isPosOnRect(GetMousePosition(), Rectangle{0, 0, 300, screenHeight})) {
                /* UI */
                for (int i = 0; i < aBtnN; i++) {
                    if (actionButtons[i]->isClicked()) {
                        if (actionButtons[i]-> GetBuildID() == buildID) {
                            buildID = BT_NULL;
                        } else {
                            buildID = actionButtons[i]->GetBuildID();
                            printf("lets build! %d", buildID);
                        }
                    }
                } 
            } else {
                if (buildID) {
                    //Branch on buildID whether to build or demolish
                    _model->Build(buildID, Vector2{static_cast<float>(gridX), static_cast<float>(gridY)});
                } else {
                    for (Field* f : (_model->_fields)) {
                        if (isPosOnRect(mouseWorldPos, f->GetRect()))
                        {
                            _model->OpenFWindow(f);
                            l = false;
                        }
                    }
                }
                // buildID = 0;
            }
            if (_model->GetFWindow() != nullptr && l) {
                _model->CloseFWindow();
            }
        }
        //wheel action
        float wheel = GetMouseWheelMove();

        if (wheel != 0)
        {
            // Get the world point that is under the mouse

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

        DrawText("$[game_name]", (screenWidth - MeasureText("$[game_name]", 60)) / 2, screenHeight / 2 - 80, 60, BLUE);

        newGameBtn->Render();
        loadGameBtn->Render();
        exitBtn->Render();

        EndDrawing();
        break;
    case GAME:
        //relative position of the mouse related to the camera
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
        
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

        for (Field *i : (_model->_fields))
        {
            i->Render();
        }

        EndMode2D();


        /* UI */
        DrawRectangle(0, 0, 300, screenHeight, RAYWHITE);
        DrawRectangle(0, 0, screenWidth, 50, RAYWHITE);
        DrawRectangle(0, screenHeight - 50, screenWidth, 50, RAYWHITE);

        for (int i = 0; i < aBtnN; i++) {
            actionButtons[i]->Render(actionButtons[i]->GetBuildID() == buildID);
        }

        if (_model->GetFWindow() != nullptr)
            _model->GetFWindow()->Render();

        DrawText(("Residental count: " + STR(resCounter)).c_str(), 20, screenHeight-40, 20, BLACK);
        DrawText(("Money: " + STR(_model->_fin_state.total_founds) + "$").c_str(), 400, screenHeight-40, 20, BLACK);

        // DrawText("Mouse right button drag to move, mouse wheel to zoom", 310, 60, 20, WHITE);

        EndDrawing();

        break;
    }
}