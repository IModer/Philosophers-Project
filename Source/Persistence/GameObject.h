#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#include "../App/global.h"

class GameObject
{
    public:
    std::string ToString();
};

class Field : public GameObject
{
    public:
    Field(int id, int x, int y, int width, int height);
    std::string ToString();

    private:
    int id;
    Vector2 pos;
    Vector2 size;
};

typedef struct {
    int money;
    // ...
} FinancialState;

class Stat : public GameObject 
{
    public:
    Stat(time_t date, FinancialState finState);
    std::string ToString();

    private:
    time_t date;
    FinancialState finantialState;
};

#endif