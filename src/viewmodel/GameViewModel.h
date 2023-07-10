#ifndef GAMEVIEWMODEL_H
#define GAMEVIEWMODEL_H
#include "../common/config.h"
#include "../util/Utility.h"
#include "../precomp.h"
class GameViewModel
{
public:
    Game *game;
    GameViewModel(Game *game) : game(game) {}
    void Update(float dt);
};

#endif // !GAMEVIEWMODEL_H