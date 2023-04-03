#ifndef GAME_OBJECT_H_DEFINED
#define GAME_OBJECT_H_DEFINED

#include <iostream>


class GameObject
{
    public:
        virtual std::string toString() = 0;
    private:
};


#endif