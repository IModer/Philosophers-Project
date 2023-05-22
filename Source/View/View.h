#ifndef _VIEW_
#define _VIEW_

#include "../App/global.h"
#include "../Model/GameModel.h"
#include "Button.h"
#include "ImgBtn.h"
#include "TimeBtn.h"
#include <raylib.h>
#include <vector>

class View 
{
    public:
    // STATIC //
    static const int screenWidth = 1920;
    static const int screenHeight = 1080;
    
    static bool isPosOnRect(Vector2 Pos, Rectangle rect);
    View(GameModel* model);
    void Update();
    void Render();
    bool exitWindowRequested = false;   // Flag to request window to exit
    bool exitWindow = false;    // Flag to set window to exit
    private:
    GameModel* _model;
    GAME_STATE gameState;
    Button* newGameBtn;
    Button* loadGameBtn;
    Button* exitBtn;
    Camera2D camera;

    private:
    SaveButton* saveBtns[10];
    static const int aBtnN = 10;
    ImgBtn* actionButtons[aBtnN];
    TimeButton* timeButtons[4];
    Button* TaxButtons[6];
    ExitButton* closeBtn;
    Button* menuBtn;
    Button* savebtn;
    BUILD_TYPES buildID;
    std::vector<INT_TOUPLE> buildPos;
    int saveNotification = 0;
};

#endif