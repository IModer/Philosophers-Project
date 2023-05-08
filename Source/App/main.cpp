#include "global.h"
#include "App.h"
    
//Run main program
int main()
{
    App* _app = App::Instance();
    _app->Run();
    //Here we can handle things that should happen after the game is closed

}