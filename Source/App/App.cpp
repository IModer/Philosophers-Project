#include "App.h"
#include <raylib.h>

App *App::_instance = nullptr;

App *App::Instance()
{
    return (_instance == nullptr) ? (new App()) : _instance;
}

void App::DeleteInstance()
{
    if (_instance != nullptr)
        delete _instance;
    _instance = nullptr;
}

App::App()
{
    //View, Model, Persistence példánmyosítása

    _persistence = new Persistence();
    
    _model = new GameModel(_persistence);
    _view = new View(_model);

    SetTargetFPS(FPS);
}

void App::Run()
{
    while (!WindowShouldClose())
    {
        std::vector<Rectangle> rects;
        _view->Update();
        _view->Render();
    }
}