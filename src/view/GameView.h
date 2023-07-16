#ifndef GAMEVIEW_H
#define GAMEVIEW_H
#include "../common/config.h"
#include "../util/Utility.h"
#include "../precomp.h"
#include <map>
#include <memory>
class GameView
{
public:
    std::shared_ptr<Game> game;
    GameView(){}
    GameView(std::shared_ptr<Game> g) : game(g) {}
    // Game *game;
    // GameView(Game *g) : game(g) {}
    void Render();
    void SetKeys(bool *Keys);
    void SetGamePointer(std::shared_ptr<Game> pg)
    {
        game = pg;
    }
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