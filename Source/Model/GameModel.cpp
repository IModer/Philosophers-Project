#include "GameModel.h"
#include <raylib.h>

void GameModel::Build(Vector2 pos, int id) {
    for(Field* f : _fields)
    {
        if(f->GetX() == pos.x && f->GetY() == pos.y)
        {
            printf("There was an overlap\n");
            if (id < 0) {
                _fields.remove(f);
            }
            return;
        }
    }
    if (id >= 0) {
        _fields.push_back(new Field(id, INT_TOUPLE{static_cast<int>(pos.x), static_cast<int>(pos.y)}, INT_TOUPLE{id==FIREDEPARTMENT?100:50, id==FIREDEPARTMENT?100:50})); // factoryval?
        money -= 100;
    }
} 