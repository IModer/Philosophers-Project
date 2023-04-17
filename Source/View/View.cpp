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
    actionButtons[0] = new ImgBtn("make rect", GAMEFIELD, Rectangle{ 10, 60, 130, 130 }, "Makes a rectangle"); 
    actionButtons[1] = new ImgBtn("del rect", -1, Rectangle{ 160, 60, 130, 130 }, "Deletes a rectangle"); 

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
            if (isPosOnRect(GetMousePosition(), Rectangle{0, 0, 300, screenHeight})) {
                /* UI */
                for (int i = 0; i < aBtnN; i++) {
                    if (actionButtons[i]->isClicked()) {
                        buildID = actionButtons[i]->GetBuildID();
                        printf("lets build! %d", buildID);
                    }
                } 
            } else {
                if (buildID) {
                    _model->Build(Vector2{static_cast<float>(gridX), static_cast<float>(gridY)}, buildID);
                } else {
                    for (Field* f : _model->_fields) {
                        if (isPosOnRect(mouseWorldPos, Rectangle{static_cast<float>(f->GetX()), static_cast<float>(f->GetY()), static_cast<float>(f->GetWidth()), static_cast<float>(f->GetHeight())}))
                        {
                            _model->OpenFWindow();

                        }
                    }
                }
                if (_model->GetFWindow() != nullptr) {
                    _model->CloseFWindow();
                }
                // buildID = 0;
            }


        }
        //wheel action
        float wheel = GetMouseWheelMove();


        // Debug rect create-delete
        if (IsKeyPressed(KEY_B))
        {
            // Do something when the "B" button is pressed
            


            printf("%f, %f", mouseWorldPos.x,mouseWorldPos.y );
            printf("The 'B' button was pressed over coordinates %d %d!\n", gridX, gridY);
            //_model->_fields.push_back(Building); itt kell pusholni
            // ez gondolom megy a build függvénybe
            // Create the rectangle
            // int rectWidth = 50;
            // int rectHeight = 50;
            // bool isOverlap = false;
            // for(Rectangle rect : rects)
            // {
            //     if(rect.x == gridX && rect.y == gridY)
            //     {
            //         isOverlap = true;
            //         printf("There was an overlap\n");
            //         break;
            //     }
            // }
            // if(!isOverlap) 
            // {
            //     Rectangle rect = { static_cast<float>(gridX), static_cast<float>(gridY), static_cast<float>(rectWidth), static_cast<float>(rectHeight) };
            //     rects.push_back(rect);
            // }

            // // Add the rectangle to the vector
            
            
            
        }
        if (IsKeyPressed(KEY_D))
        {
            printf("The 'D' button was pressed!\n");

            int gridX = static_cast<int>(mouseWorldPos.x / 50) * 50;
            if(mouseWorldPos.x < 0.0)
            {
                printf("insideif\n");
                gridX -= 50;
            }
            int gridY = static_cast<int>(mouseWorldPos.y / 50) * 50;
            if(mouseWorldPos.y < 0.0)
            {
                printf("insideif\n");
                gridY = gridY -50;
            }
            for(int i = 0; i < rects.size(); i++)
            {
                if(rects[i].x == gridX && rects[i].y == gridY)
                {
                    rects.erase(rects.begin() + i);
                    printf("Rect was deleted\n");
                    break;
                }
            }
        }

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
        
        //right click
        
        // Draw the 3d grid, rotated 90 degrees and centered around 0,0
        // just so we have something in the XY plane
        rlPushMatrix();
        rlTranslatef(0, 25 * 50, 0);
        rlRotatef(90, 1, 0, 0);
        DrawGrid(100, 50);
        rlPopMatrix();


        DrawRectangle(0, 0, 50, 50, YELLOW);
        for (int i = 0; i < rects.size(); i++)
        {
            DrawRectangleRec(rects[i], RED);
        }
        EndMode2D();


        /* UI */
        DrawRectangle(0, 0, 300, screenHeight, RAYWHITE);
        DrawRectangle(0, 0, screenWidth, 50, RAYWHITE);
        DrawRectangle(0, screenHeight - 50, screenWidth, 50, RAYWHITE);

        for (int i = 0; i < 2; i++) {
            actionButtons[i]->Render();
        }

        if (_model->GetFWindow() != nullptr)
            _model->GetFWindow()->Render();

        DrawText("Mouse right button drag to move, mouse wheel to zoom", 310, 60, 20, WHITE);

        EndDrawing();
        for (Field *i : _model->_fields)
        {
            i->Render();
        }
        break;
    }
}