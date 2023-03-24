#include "../Header/global.h"
#include "../Header/Game.h"

int main()
{
    InitWindow(400, 400, "test");
    SetTargetFPS(60);

    Game* game = Game::Instance();

    while(!WindowShouldClose()){
        game->GameLoop();
    }   
}