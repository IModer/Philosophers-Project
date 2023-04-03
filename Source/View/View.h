#ifndef _VIEW_
#define _VIEW_

#include "../App/global.h"
#include "../Model/GameModel.h"

class View 
{
    public:
    View(GameModel* model);
    void Update();
    void Render();
    private:
    GameModel* _model;
    GAME_STATE gameState;
};

#endif