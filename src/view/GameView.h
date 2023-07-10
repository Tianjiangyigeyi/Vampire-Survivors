#ifndef GAMEVIEW_H
#define GAMEVIEW_H
#include "../common/config.h"
#include "../util/Utility.h"
#include "../precomp.h"
class GameView
{
public:
    Game* game;
    GameView(Game *game) : game(game) {}
    void ProcessInput(float dt);
    void Render();
};

#endif // !GAMEVIEW_H