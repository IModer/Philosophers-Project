#include "App.h"

App *App::Instance()
{
    return (_instance == nullptr) ? (new App()) : _instance;
}

void App::DeleteInstance()
{
    if (_instance != nullptr)
        delete _instance;
    _instance = nullptr;
};

App::App()
{
    //View, Model, Persistence példánmyosítása

    //_view = View::Instance();
    _model = Game::Instance();  //Vagy a view csináljon saját Model-t?
    //_persistence = ?


}

void App::Run()
{
    //
}