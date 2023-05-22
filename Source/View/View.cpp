#include "View.h"
#include "Button.h"
#include "ImgBtn.h"
#include "rlgl.h"
#include "raymath.h"
#include "../Model/FloatingWindow.h"
#include <cstdio>
#include <ctime>
#include <raylib.h>
#include <stdlib.h>
#include <format>

bool View::isPosOnRect(Vector2 Pos, Rectangle rect)
{
    return Pos.x > rect.x && Pos.x < rect.x + rect.width && Pos.y > rect.y && Pos.y < rect.y + rect.height;
}

View::View(GameModel *model)
{
    _model = model;
    gameState = MENU;
    buildID = BT_NULL;

    InitWindow(screenWidth, screenHeight, "$[Game_name]");
    SetWindowState(FLAG_FULLSCREEN_MODE);
    

    /* Menu buttons */
    newGameBtn = new Button("New game", Rectangle{screenWidth / 2.f - 200, screenHeight / 2.f, 400, 80}, 40);
    loadGameBtn = new Button("Load game", Rectangle{screenWidth / 2.f - 200, screenHeight / 2.f + 100, 400, 80}, 40);
    exitBtn = new Button("Exit game", Rectangle{screenWidth / 2.f - 200, screenHeight / 2.f + 200, 400, 80}, 40);

    /* Save Buttons */
    for (int i = 0; i < 10; i++) {
        saveBtns[i] = new SaveButton({(screenWidth-400)/2.f, 200+i*60.f, 400, 40}, i+1, _model->numOfSaves > i);
    }
    loadExitBtn = new Button("Back", Rectangle{(screenWidth-400)/2.f, 800, 400, 40}, 40);

    /* Action Buttons */
    int n = 0;
    for (std::pair<FIELD_TYPES, std::string> i : BuildingNames)
    {
        actionButtons[n] = new ImgBtn(i.second, static_cast<BUILD_TYPES>(i.first), Rectangle{10 + (n % 2) * 150.f, 60 + (n / 2) * 150.f, 130, 130}, "Builds a new " + i.second + " Cost: " + STR(BuildCosts.at(i.first)) + "$");
        n++;
    }
    actionButtons[aBtnN - 1] = new ImgBtn("Demolition", BT_DEMOLISH, Rectangle{10 + (n % 2) * 150.f, 60 + (n / 2) * 150.f, 130, 130}, "Demolishes buildings");

    timeButtons[0] = new TimeButton("Pause", PAUSE, Rectangle{10, 880, 130, 60}, "Pauses the game.");
    timeButtons[1] = new TimeButton("Normal", NORMAL, Rectangle{160, 880, 130, 60}, "Normal speed (1 sec = 1 day)");
    timeButtons[2] = new TimeButton("Fast", FAST, Rectangle{10, 950, 130, 60}, "Fast speed (1 sec = 2 days)");
    timeButtons[3] = new TimeButton("Faster", FASTER, Rectangle{160, 950, 130, 60}, "Faster speed (1 sec = 3 days)");

    for (int i = 0; i < 6; i+=2) {
        TaxButtons[i] = new Button("-", {screenWidth - 240 - i*120.f, screenHeight-45.f, 40, 40}, 32);
        TaxButtons[i+1] = new Button("+", {screenWidth - 50 - i*120.f, screenHeight-45.f, 40, 40}, 32);
    }

    menuBtn = new Button("MENU", Rectangle{5, 5, 120, 40}, 36);
    savebtn = new Button("SAVE", Rectangle{130, 5, 120, 40}, 36);
    closeBtn = new ExitButton(Rectangle{screenWidth - 50, 5, 40, 40});

    camera = {0};
    camera.zoom = 1.0f;

    SetExitKey(KEY_NULL); // Disable KEY_ESCAPE to close window, X-button still works

    SetTargetFPS(60);

    Field::images = LoadTexture("../Assets/tiles.png");
};

void View::Update()
{
    switch (gameState)
    {
    case MENU:
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (newGameBtn->isClicked())
            {
                gameState = GAME;
                _model->NewGame();
            }
            if (loadGameBtn->isClicked())
            {
                gameState = LOAD;
            }
            if (exitBtn->isClicked())
            {
                CloseWindow();
                //return 0;
                exit(0);
            }
        }
        break;
    case LOAD:
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            for (int i = 0; i < 10; i++) {
                if (saveBtns[i]->isClicked()) _model->LoadGame(i+1);
                gameState = GAME;
                break;
            }
            if (loadExitBtn->isClicked()) gameState = MENU;
        }
        break;
    case GAME:
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        // Round the position to the nearest multiple of 50
        int gridX = static_cast<int>(mouseWorldPos.x / 50) * 50;
        if (mouseWorldPos.x < 0.0)
        {
            // printf("insideif\n");
            gridX -= 50;
        }
        int gridY = static_cast<int>(mouseWorldPos.y / 50) * 50; // ez jó
        if (mouseWorldPos.y < 0.0)
        {
            // printf("insideif\n");
            gridY = gridY - 50;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f / camera.zoom);

            camera.target = Vector2Add(camera.target, delta);
        }
        // left click
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && buildID > 0)
        {
            INT_TOUPLE pos = INT_TOUPLE{gridX, gridY};
            bool l = true;
            for (INT_TOUPLE i : buildPos)
            {
                if (CheckCollisionRecs(Rectangle{static_cast<float>(pos.x), static_cast<float>(pos.y), BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).x * M_UNIT * 1.f, BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).y * M_UNIT * 1.f},
                                       Rectangle{static_cast<float>(i.x), static_cast<float>(i.y), BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).x * M_UNIT * 1.f, BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).y * M_UNIT * 1.f}))
                {
                    l = false;
                    break;
                }
            }
            if (l)
                buildPos.push_back(pos);
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && buildID > 0)
        {
            INT_TOUPLE pos = INT_TOUPLE{gridX, gridY};
            bool l = true;
            for (INT_TOUPLE i : buildPos)
            {
                if (CheckCollisionRecs(Rectangle{static_cast<float>(pos.x), static_cast<float>(pos.y), BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).x * M_UNIT * 1.f, BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).y * M_UNIT * 1.f},
                                       Rectangle{static_cast<float>(i.x), static_cast<float>(i.y), BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).x * M_UNIT * 1.f, BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).y * M_UNIT * 1.f}))
                {
                    l = false;
                    break;
                }
            }
            if (l)
                buildPos.push_back(pos);
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            bool l = true;
            if (isPosOnRect(GetMousePosition(), Rectangle{0, 50, 300, static_cast<float>(screenHeight)}))
            {
                /* UI */
                for (int i = 0; i < aBtnN; i++)
                {
                    if (actionButtons[i]->isClicked())
                    {
                        if (actionButtons[i]->GetBuildID() == buildID)
                        {
                            buildID = BT_NULL;
                        }
                        else
                        {
                            buildID = actionButtons[i]->GetBuildID();
                        }
                    }
                }
                for (int i = 0; i < 4; i++)
                {
                    if (timeButtons[i]->isClicked())
                    {
                        _model->speedOfTime = timeButtons[i]->getTime();
                    }
                }
            }
            else if (isPosOnRect(GetMousePosition(), {screenWidth - 720, screenHeight - 45, 710, 40})) {
                if (TaxButtons[0]->isClicked()) _model->SetResidentialTaxRate(_model->GetResidentialTaxRate()-0.01f);
                if (TaxButtons[1]->isClicked()) _model->SetResidentialTaxRate(_model->GetResidentialTaxRate()+0.01f);
                if (TaxButtons[2]->isClicked()) _model->SetIndustrialTaxRate(_model->GetIndustrialTaxRate()-0.01f);
                if (TaxButtons[3]->isClicked()) _model->SetIndustrialTaxRate(_model->GetIndustrialTaxRate()+0.01f);
                if (TaxButtons[4]->isClicked()) _model->SetServiceTaxRate(_model->GetServiceTaxRate()-0.01f);
                if (TaxButtons[5]->isClicked()) _model->SetServiceTaxRate(_model->GetServiceTaxRate()+0.01f);
            }
            else if (savebtn->isClicked()) {
                _model->SaveGame();
                saveNotification = 60;
            }
            else if (menuBtn->isClicked()) {
                gameState = MENU;
            }
            else if (closeBtn->isClicked()) {
                exitWindowRequested = true;
            }
            else
            {
                if (buildID)
                {
                    if (buildID > 0)
                    {
                        _model->Build(static_cast<FIELD_TYPES>(buildID), &buildPos);
                    }
                    else
                        _model->Demolition(mouseWorldPos);
                }
                else if (_model->GetFWindow() != nullptr && _model->GetFWindow()->IsMouseOver()) {
                    _model->GetFWindow()->OnClick(GetMousePosition());
                }
                else
                {
                    for (Field *f : (_model->_fields))
                    {
                        if (isPosOnRect(mouseWorldPos, f->GetRect()))
                        {
                            _model->OpenFWindow(f);
                            l = false;
                        }
                    }
                }
                // buildID = 0;
            }
            if (_model->GetFWindow() != nullptr && l)
            {
                _model->CloseFWindow();
            }
            if (!buildPos.empty())
                buildPos.clear();
        }
        if (IsKeyReleased(KEY_C)) {
            _model->CauseCatastrophe();
        }
        if (IsKeyReleased(KEY_S)) {
            _model->SaveGame();
            saveNotification = 60;
        }
        // wheel action
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
        //_model->Update();
        _model->TickTock();
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
    case LOAD:
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < 10; i++) saveBtns[i]->Render();
        loadExitBtn->Render();

        EndDrawing();
        break;
    case GAME:
        // relative position of the mouse related to the camera
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        BeginDrawing();
        ClearBackground(BLUE);
        BeginMode2D(camera);
        DrawRectangle(-50 * M_UNIT, -25 * M_UNIT, 100 * M_UNIT, 50 * M_UNIT, DARKGREEN);
        DrawRectangle(0, -26*M_UNIT, M_UNIT, M_UNIT, Color{74, 84, 98, 255});

        // Draw the 3d grid, rotated 90 degrees and centered around 0,0
        // just so we have something in the XY plane
        if (buildID != 0) {
            rlPushMatrix();
            rlTranslatef(0, 25 * 50, 0);
            rlRotatef(90, 1, 0, 0);
            DrawGrid(100, 50);
            rlPopMatrix();
        }

        for (Field *i : (_model->_fields))
        {
            // i->Render();
            if (i->GetId() == ROADANDELECTRICPOLE)
            {
                i->Render();
            }
            else
            {
                DrawTexturePro(Field::images, i->GetSourceRect(), i->GetDrawRect(), {0, 0}, 0.f, ((GameField*)i)->HasElectricity()?WHITE:DARKGRAY);
                if (((GameField*)i)->IsOnFire()) DrawTexturePro(Field::images, fireSourceRect[(_model->stat._time%30)/15], i->GetDrawRect(), {0, 0}, 0.f, WHITE);
            }
        }
        if (_model->GetFWindow() != nullptr) _model->GetFWindow()->RenderExtra();

        // Build place
        Vector2 MouseGridPos = Vector2{floor(mouseWorldPos.x / 50) * 50, floor(mouseWorldPos.y / 50) * 50};
        if (mouseWorldPos.x < 0.0)
            MouseGridPos.x -= 50;
        if (mouseWorldPos.y < 0.0)
            MouseGridPos.y = MouseGridPos.y - 50;

        if (buildID > 0)
        {
            if (MouseGridPos.x >= 0 && MouseGridPos.y >= 0)
            {
                DrawRectangleV(MouseGridPos,
                               Vector2{BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).x * M_UNIT * 1.f,
                                       BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).y * M_UNIT * 1.f},
                               Color{255, 255, 255, 100});
            }
            else if (MouseGridPos.x < 0 && MouseGridPos.y < 0)
            {
                DrawRectangleV(Vector2{MouseGridPos.x + 50, MouseGridPos.y + 50},
                               Vector2{BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).x * M_UNIT * 1.f,
                                       BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).y * M_UNIT * 1.f},
                               Color{255, 255, 255, 100});
            }
            else if (MouseGridPos.x >= 0 && MouseGridPos.y < 0)
            {
                DrawRectangleV(Vector2{MouseGridPos.x, MouseGridPos.y + 50},
                               Vector2{BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).x * M_UNIT * 1.f,
                                       BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).y * M_UNIT * 1.f},
                               Color{255, 255, 255, 100});
            }
            else if (MouseGridPos.x < 0 && MouseGridPos.y >= 0)
            {
                DrawRectangleV(Vector2{MouseGridPos.x + 50, MouseGridPos.y},
                               Vector2{BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).x * M_UNIT * 1.f,
                                       BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).y * M_UNIT * 1.f},
                               Color{255, 255, 255, 100});
            }
        }
        else if (buildID == BT_DEMOLISH)
        {
            if (MouseGridPos.x >= 0 && MouseGridPos.y >= 0)
            {
                DrawRectangleV(MouseGridPos, Vector2{M_UNIT, M_UNIT}, Color{255, 0, 0, 100});
            }
            else if (MouseGridPos.x < 0 && MouseGridPos.y < 0)
            {
                DrawRectangleV(Vector2{MouseGridPos.x + 50, MouseGridPos.y + 50}, Vector2{M_UNIT, M_UNIT}, Color{255, 0, 0, 100});
            }
            else if (MouseGridPos.x >= 0 && MouseGridPos.y < 0)
            {
                DrawRectangleV(Vector2{MouseGridPos.x, MouseGridPos.y + 50}, Vector2{M_UNIT, M_UNIT}, Color{255, 0, 0, 100});
            }
            else if (MouseGridPos.x < 0 && MouseGridPos.y >= 0)
            {
                DrawRectangleV(Vector2{MouseGridPos.x + 50, MouseGridPos.y}, Vector2{M_UNIT, M_UNIT}, Color{255, 0, 0, 100});
            }
        }
        if (!buildPos.empty())
        {
            for (INT_TOUPLE p : buildPos)
            {
                DrawRectangle(p.x, p.y, BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).x * M_UNIT, BuildingSizes.at(static_cast<FIELD_TYPES>(buildID)).y * M_UNIT, Color{0, 200, 0, 100});
            }
        }

        EndMode2D();

        /* UI */
        DrawRectangle(0, 0, 300, screenHeight, LIGHTGRAY);
        DrawRectangle(0, 0, screenWidth, 50, RAYWHITE);
        DrawRectangle(0, screenHeight - 50, screenWidth, 50, RAYWHITE);

        menuBtn->Render();
        savebtn->Render();
        closeBtn->Render();

        for (int i = 0; i < aBtnN; i++)
        {
            actionButtons[i]->Render(actionButtons[i]->GetBuildID() == buildID);
        }
        for (int i = 0; i < aBtnN; i++)
        {
            actionButtons[i]->RenderText();
        }

        DrawText("Game speed", (300 - MeasureText("Game speed", 28)) / 2, 840, 28, BLACK);

        for (int i = 0; i < 4; i++)
        {
            timeButtons[i]->Render(_model->speedOfTime);
        }
        for (int i = 0; i < 4; i++)
        {
            timeButtons[i]->RenderText();
        }

        DrawRectangle(screenWidth - 720, screenHeight - 45, 710, 40, LIGHTGRAY);
        for (int i = 0; i < 6; i++) TaxButtons[i]->Render();

        if (_model->GetFWindow() != nullptr)
            _model->GetFWindow()->Render(_model);

        DrawRectangle(8, screenHeight - 45, 180, 40, LIGHTGRAY);
        DrawText(("Date: " + _model->GetCurrentDate()).c_str(), 20, screenHeight - 32, 20, BLACK);
        DrawRectangle(198, screenHeight - 45, 200, 40, LIGHTGRAY);
        DrawText(("Satisfaction: " + STR(_model->satisfaction)).c_str(), 210, screenHeight - 32, 20, BLACK);
        DrawRectangle(408, screenHeight - 45, 200, 40, LIGHTGRAY);
        DrawText(("Money: " + STR(_model->stat._finState.total_founds) + "$").c_str(), 420, screenHeight - 32, 20, BLACK);

        DrawText(("Res. Tax: " + STR((int)(_model->GetResidentialTaxRate()*100)) + "%").c_str(), screenWidth - 195, screenHeight - 32, 20, BLACK);
        DrawText(("Ind. Tax: " + STR((int)(_model->GetIndustrialTaxRate()*100)) + "%").c_str(), screenWidth - 435, screenHeight - 32, 20, BLACK);
        DrawText(("Ser. Tax: " + STR((int)(_model->GetServiceTaxRate()*100)) + "%").c_str(), screenWidth - 675, screenHeight - 32, 20, BLACK);


        DrawText("Mouse right button drag to move, mouse wheel to zoom | ESC - QUIT | S - SAVE | C - cause catastrope", 310, 60, 20, WHITE);   
        if (saveNotification) {
            DrawText("Game saved!", 310, 100, 20, WHITE);
            saveNotification--;
        }
        if (_model->Gameover == true)
        {
            DrawText("GAME OVER", screenWidth / 2 - 500, screenHeight / 2, 100, WHITE);
        }

        if (exitWindowRequested)
        {
            DrawRectangle(0, 100, screenWidth, 200, BLACK);
            DrawText("Are you sure you want to exit program? [Y/N]", 40, 180, 30, WHITE);
            if (IsKeyPressed(KEY_Z)) //idióta amerikaiak, ez az y
            {
                CloseWindow();
                exit(0);
            }
            
            else if (IsKeyPressed(KEY_N)) exitWindowRequested = false;
        }
        
        

        EndDrawing();

        break;
    }
}