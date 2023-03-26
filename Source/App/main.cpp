#include "global.h"
#include "App.h"

//TODO remove this
#include "../Model/Game.h"

int main()
{
    App* _app = App::Instance();
    _app->Run();
    //Here we can handle things that should happen after the game is closed

    // This should be View code
    //  |
    //  V
    InitWindow(400, 400, "test");
    SetTargetFPS(60);

    Game* game = Game::Instance();

    while(!WindowShouldClose()){
        game->GameLoop();
    }   
}