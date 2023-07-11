#include "GameView.h"

extern double cursor_x, cursor_y;
extern bool LeftButtonPressed;

void GameView::ProcessInput(float dt)
{
    if (game->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        glm::vec2 dir = glm::vec2(0.0f, 0.0f);
        // move playerboard
        if (game->Keys[GLFW_KEY_A])
        {
            if (game->Player->Position.x >= 0.0f)
                dir.x -= 1;
        }
        if (game->Keys[GLFW_KEY_D])
        {
            if (game->Player->Position.x <= game->BG_Width - ResourceManager::GetTexture(game->Player->Sprite).Width)
                dir.x += 1;
        }
        if (game->Keys[GLFW_KEY_W])
        {
            if (game->Player->Position.y >= 0.0f)
                dir.y -= 1;
        }
        if (game->Keys[GLFW_KEY_S])
        {
            if (game->Player->Position.y <= game->BG_Height - ResourceManager::GetTexture(game->Player->Sprite).Height)
                dir.y += 1;
        }
        if (dir != glm::vec2(0.0f, 0.0f))
        {
            dir = glm::normalize(dir) * velocity;
        }
        // TODO : 这里最好用notification实现函数的调用，具体的操作暂时还不会
        game->Player->Move(dir);
        game->Player->the_weapon->Move(dir);
    }
}

void GameView::Render()
{
    if (game->State == GAME_ACTIVE)
    {
        // 每次渲染必须reset相机位置, scale是缩放的比例
        float scale = 0.5;
        Utility::ResetCamera(game->Player->Position, glm::vec2(game->Width / 2.0f, game->Height / 2.0f), scale);
        // std::cout<<Player->Position.x<<" "<<Player->Position.y<<std::endl;
        // std::cout<<Width<<" "<<Height<<std::endl;
        // draw background
        Utility::DrawBackground();
        game->Player->Draw();
        game->Player->the_weapon->Draw();
        for (auto it = game->Enemy.begin(); it != game->Enemy.end(); it++)
            (*it)->Draw();
    }
    if (game->State == GAME_START_MENU)
    {
        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("StartMenu"));

        Button start_button(game->Width * 0.45, game->Height * 0.9, game->Width * 0.1, game->Height * 0.05, std::string("StartM    start"));
        start_button.DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        if (start_button.pressed)
        {
            game->State = GAME_ACTIVE;
        }

        // game->State = GAME_ACTIVE;
        // std::cout <<"here"<<cursor_x<<std::endl;
        // sleep(1);
    }
}