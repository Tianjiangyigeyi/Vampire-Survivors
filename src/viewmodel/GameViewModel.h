#ifndef GAMEVIEWMODEL_H
#define GAMEVIEWMODEL_H
#include "../common/config.h"
#include "../util/Utility.h"
#include "../precomp.h"
#include <memory>
class GameViewModel
{
public:
    std::shared_ptr<Game> game;
    GameViewModel() : game(std::make_shared<Game>(WINDOW_WIDTH, WINDOW_HEIGHT)) {}
    // Game* game;
    // GameViewModel(Game* g) : game(g) {}
    void Update(float dt);
    std::shared_ptr<Game> GetGamePointer()
    {
        return game;
    }
};

#endif // !GAMEVIEWMODEL_H