#ifndef GAMEVIEW_H
#define GAMEVIEW_H
#include "../common/config.h"
#include "../util/Utility.h"
#include "../precomp.h"
#include <map>
class GameView
{
public:
    Game* game;
    GameView(Game *game) : game(game) {}
    void ProcessInput(float dt);
    void Render();
};

class SelectMenu
{
public:
    static void RenderPeopleSelect(double x, double y, bool button_left);
    static void RenderWeaponSelect(double x, double y, bool button_left);
    static void RenderMapSelect(double x, double y, bool button_left);
    static void RenderPropSelect(double x, double y, bool button_left);


};

#endif // !GAMEVIEW_H