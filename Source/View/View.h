#ifndef _VIEW_
#define _VIEW_

#include "../App/global.h"
#include "../Model/GameModel.h"
#include "Button.h"
#include <raylib.h>

class View 
{
    public:
    // STATIC //
    static const int screenWidth = 1920;
    static const int screenHeight = 1080;
    static bool isMouseOnRect(Rectangle rect);

    View(GameModel* model);
    void Update();
    void Render();
    private:
    GameModel* _model;
    GAME_STATE gameState;
    Button* newGameBtn;
    Button* loadGameBtn;
    Button* exitBtn;
    Camera2D camera;
};

#endif