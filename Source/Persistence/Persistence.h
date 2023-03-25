#include "../App/global.h"
#include "GameObject.h"

class Persistence
{
    public:
    std::vector<GameObject*> ReadGameState(std::string fileName);
    bool WriteGameState(std::string fileName, std::vector<GameObject*> gameObjects);
};