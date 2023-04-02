#ifndef _VIEW_
#define _VIEW_

#include "../App/global.h"
#include "../Model/GameModel.h"

class View 
{
    public:
    View(GameModel* model): _model(model) {};
    void Render();
    private:
    GameModel* _model;
};

#endif