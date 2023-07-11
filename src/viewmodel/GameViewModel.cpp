#include "GameViewModel.h"
int Ecount;
void GameViewModel::Update(float dt)
{
    Ecount++;
    if (Ecount >= 90)
    {
        Ecount = 0;
        glm::vec2 enemyPos, dir;
        unsigned int len = rand() % (game->Height * 2 + game->Width * 2);

        std::string the_enemy = "enemy";

        if (len < game->Height)
        {   
            dir = glm::vec2(game->Width + ResourceManager::GetTexture(the_enemy).Width, len * 2.0 - game->Height);
            dir.x = -dir.x;
        }

        else if (len < game->Height + game->Width)
        {
            dir = glm::vec2(len * 2.0 - game->Height * 2.0 - game->Width, game->Height + ResourceManager::GetTexture(the_enemy).Height);
            dir.y = -dir.y;
        }

        else if (len < 2 * game->Height + game->Width)
            dir = glm::vec2(game->Width, len * 2.0 - game->Height * 3.0 - game->Width * 2.0);

        else
            dir = glm::vec2(len * 2.0 - game->Height * 4.0 - game->Width * 3, game->Height);

        enemyPos = game->Player->Position + dir;
        EnemyObject *temp = new EnemyObject(enemyPos, the_enemy);
        game->Enemy.push_back(temp);

        for (auto it = game->Enemy.begin(); it != game->Enemy.end(); it++)
        {
            if((*it)->CheckCollision(*game->Player->the_weapon)){
                game->Enemy.erase(it, it+1);
                continue;
            }
            glm::vec2 dir1 = glm::vec2(game->Player->Position.x - (*it)->Position.x, game->Player->Position.y - (*it)->Position.y);
            dir1 = glm::normalize(dir1);
            (*it)->Move(dir1);
        }
    }
}