#ifndef _GAME_
#define _GAME_

#include "../App/global.h"

class Game
{
    public:
    // static
    static Game* Instance();
    static void DeleteInstance();
    // get-set

    // functions
    Game();
    void GameLoop();
    private:
    // static
    static Game* _instance;
    // variables

    // functions
};


#endif