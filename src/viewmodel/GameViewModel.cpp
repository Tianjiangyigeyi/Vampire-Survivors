#include "GameViewModel.h"

void GameViewModel::Update(float dt)
{
    if (game->State == GAME_ACTIVE)
    {
        game->dir *= PLAYER_VELOCITY * dt;
        game->Player->Move(game->dir);
        game->Player->the_weapon->Move(game->dir);
        // game->dir = glm::vec2(0.0f, 0.0f);
    }
    int total_dam = 0;
    game->timer++;
    if (game->timer % 90==0)
    {
        for(int i=0;i<1+game->timer/9000;i++)
        {
            glm::vec2 enemyPos, dir;
            unsigned int len = rand() % (game->Height * 2 + game->Width * 2);

            std::string the_enemy = "enemy";

            if (len < game->Height) {
                dir = glm::vec2(game->Width + ResourceManager::GetTexture(the_enemy).Width, len * 2.0 - game->Height);
                dir.x = -dir.x;
            } else if (len < game->Height + game->Width) {
                dir = glm::vec2(len * 2.0 - game->Height * 2.0 - game->Width,
                                game->Height + ResourceManager::GetTexture(the_enemy).Height);
                dir.y = -dir.y;
            } else if (len < 2 * game->Height + game->Width)
                dir = glm::vec2(game->Width, len * 2.0 - game->Height * 3.0 - game->Width * 2.0);

            else
                dir = glm::vec2(len * 2.0 - game->Height * 4.0 - game->Width * 3, game->Height);

            enemyPos = game->Player->Position + dir;
            EnemyObject *temp = new EnemyObject(enemyPos, the_enemy);
            temp->speed += game->timer / MAX_FRAME_PER_SECOND / 900;
            if (temp->speed > 0.2) temp->speed = 0.2;
            temp->power += game->timer / MAX_FRAME_PER_SECOND / 300;
            temp->health += game->timer / MAX_FRAME_PER_SECOND / 15;
            game->Enemy.push_back(temp);
        }

        for (auto it = game->Enemy.begin(); it != game->Enemy.end(); it++)
        {
            if ((*it)->CheckCollision(*game->Player->the_weapon))
            {
                (*it)->Destroyed = 90;
                if (!(*it)->health_adjust(game->Player->might + game->Player->the_weapon->base_damage))
                {
                    PickupObject *temp1 = new PickupObject((*it)->Position, "Experience");
                    EnemyObject *temp2 = *it;
                    game->Enemy.erase(it, it + 1);
                    it--;
                    delete temp2;

                    game->Exp.push_back(temp1);
                    continue;
                }
            }
            if ((*it)->CheckCollision(*game->Player))
            {
                if ((*it)->power > total_dam)
                    total_dam = (*it)->power;
            }
        }

        int expcount = 0;
        for (auto it1 = game->Exp.begin(); it1 != game->Exp.end(); it1++)
        {
            if ((*it1)->CheckCollision(*game->Player))
            {
                PickupObject *temp3 = *it1;
                game->Exp.erase(it1, it1 + 1);
                it1--;
                delete temp3;
                expcount += 1;
            }
        }
        game->Player->exp += expcount;
        if (game->Player->exp >= game->Player->next_exp)
        {
            game->Player->exp = 0;
            game->Player->next_exp = game->Player->next_exp * 4;
            game->State = GAME_LEVEL_UP;
            // reset_render();
        }

        if (total_dam)
            game->Player->Destroyed = 90;
        if (!game->Player->health_adjust(total_dam))
        {
            game->State = GAME_OVER;
        }
    }

    for (auto it = game->Enemy.begin(); it != game->Enemy.end(); it++)
    {
        glm::vec2 dir1 = glm::vec2(game->Player->Position.x - (*it)->Position.x, game->Player->Position.y - (*it)->Position.y);
        dir1 = glm::normalize(dir1);
        dir1 = glm::vec2(dir1.x * (*it)->speed, dir1.y * (*it)->speed);
        (*it)->Move(dir1);
    }

    for (auto it1 = game->Exp.begin(); it1 != game->Exp.end(); it1++)
    {
        if (game->Player->CheckColl(**it1))
        {
            glm::vec2 dir1 = glm::vec2(game->Player->Position.x - (*it1)->Position.x, game->Player->Position.y - (*it1)->Position.y);
            dir1 = glm::normalize(dir1);
            dir1 = glm::vec2(dir1.x * (*it1)->speed, dir1.y * (*it1)->speed);
            (*it1)->Move(dir1);
        }
    }
}