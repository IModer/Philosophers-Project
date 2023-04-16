#include "View.h"
#include <raylib.h>
#include "rlgl.h"
#include "raymath.h"
#include "../Model/FloatingWindow.h"

bool View::isPosOnRect(Vector2 Pos, Rectangle rect)
{
    return Pos.x > rect.x && Pos.x < rect.x + rect.width && Pos.y > rect.y && Pos.y < rect.y + rect.height;
}

View::View(GameModel *model)
{
    _model = model;
    gameState = MENU;

    InitWindow(screenWidth, screenHeight, "$[Game_name]");

    newGameBtn = new Button("New game", Rectangle{screenWidth / 2.f - 200, screenHeight / 2.f, 400, 80}, 40);
    loadGameBtn = new Button("Load game", Rectangle{screenWidth / 2.f - 200, screenHeight / 2.f + 100, 400, 80}, 40);
    exitBtn = new Button("Exit game", Rectangle{screenWidth / 2.f - 200, screenHeight / 2.f + 200, 400, 80}, 40);

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

         

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f / camera.zoom);

            camera.target = Vector2Add(camera.target, delta);
        }
        //left click
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if (isPosOnRect(mouseWorldPos, Rectangle{100, 100, 50, 50}))
            {
                // DrawText("Mouse ur mum", GetMouseX() + 10, GetMouseY() + 10, 20, WHITE);
                _model->OpenFWindow();

            } else if (_model->GetFWindow() != nullptr) {
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
        
        if (IsKeyPressed(KEY_B))
        {
            // Do something when the "B" button is pressed
            

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
            printf("%f, %f", mouseWorldPos.x,mouseWorldPos.y );
            printf("The 'B' button was pressed over coordinates %d %d!\n", gridX, gridY);
            //_model->_fields.push_back(Building); itt kell pusholni
            // ez gondolom megy a build függvénybe
            // Create the rectangle
            int rectWidth = 50;
            int rectHeight = 50;
            bool isOverlap = false;
            for(Rectangle rect : rects)
            {
                if(rect.x == gridX && rect.y == gridY)
                {
                    isOverlap = true;
                    printf("There was an overlap\n");
                    break;
                }
            }
            if(!isOverlap) 
            {
                Rectangle rect = { static_cast<float>(gridX), static_cast<float>(gridY), static_cast<float>(rectWidth), static_cast<float>(rectHeight) };
                rects.push_back(rect);
            }

            // Add the rectangle to the vector
            
            
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

        if (_model->GetFWindow() != nullptr)
            _model->GetFWindow()->Render();

        DrawText("Mouse right button drag to move, mouse wheel to zoom", 10, 10, 20, WHITE);

        EndDrawing();
        // for (Field *i : _model->_fields)
        // {
        //     i->Render(); //? mennyire szigorú a view-model?
        // }
        break;
    }
}