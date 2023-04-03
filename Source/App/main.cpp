#include "global.h"
#include "App.h"

//TODO remove this
#include "../Model/GameModel.h"

int main()
{
    App* _app = App::Instance();
    _app->Run();
    //Here we can handle things that should happen after the game is closed

    // This should be View code
    //  |
    //  V

}