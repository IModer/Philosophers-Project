#include "../Header/Game.h"

Game* Game::_instance = nullptr;

Game* Game::Instance()
{
    return (_instance==nullptr)?(new Game()):_instance;
}

void Game::DeleteInstance()
{
    if (_instance != nullptr) delete _instance;
    _instance = nullptr;
}

Game::Game()
{

}

void Game::GameLoop()
{
    ///// UPDATE //////


    ///// RENDER //////

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawRectangle(150, 150, 100, 100, RED);
        } EndDrawing();
}