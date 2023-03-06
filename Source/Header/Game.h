#ifndef _GAME_
#define _GAME_

#include "global.h"
#include <raylib.h>

class Game
{
    public:
    // static
    static Game* Instance();
    static void DeleteInstance();
    // get-set

    // functions
    Game();
    private:
    // static
    static Game* _instance;
    // variables

    // functions
};


#endif