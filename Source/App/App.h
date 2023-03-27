#ifndef _APP_
#define _APP_

#include "../View/View.h"
#include "../Model/GameModel.h" //TODO : rename to Model
#include "../Persistence/persistence.h"

class App
{
    public:
    // fields

    //TODO Should be Model*
    GameModel* _model;
    // TODO Need view for this
    // View* App::_view;
    Persistence* _persistence;

    // static
    static App* Instance();
    static void DeleteInstance();
    // get-set

    // functions
    App();
    void Run();
    private:
    // static
    static App* _instance;
    // variables

    // functions
};

#endif