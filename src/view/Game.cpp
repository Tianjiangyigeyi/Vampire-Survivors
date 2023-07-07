#include "Game.h"
#include <vector>

PlayerObject *Player;

float deltaTime = 0;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height), Button_left(false)
{
}

Game::~Game()
{
    delete Utility::GetRenderer();
    delete Player;
}

void Game::Init()
{
    Utility::Init();
    glm::vec2 playerPos = glm::vec2(
        this->Width / 2.0f, this->Height / 2.0f);
    Player = new PlayerObject(playerPos, ResourceManager::GetTexture("player4"), ResourceManager::GetTexture("player1"), ResourceManager::GetTexture("player2"), ResourceManager::GetTexture("player3"));

}



void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        glm::vec2 dir = glm::vec2(0.0f, 0.0f);
        // move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0.0f)
                dir.x -= 1;
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= this->Width)
                dir.x += 1;
        }
        if (this->Keys[GLFW_KEY_W])
        {
            if (Player->Position.y >= 0.0f)
                dir.y -= 1;
        }
        if (this->Keys[GLFW_KEY_S])
        {
            if (Player->Position.y <= this->Height)
                dir.y += 1;
        }
        if (dir != glm::vec2(0.0f, 0.0f))
        {
            dir = glm::normalize(dir) * velocity;
        }
        Player->Move(dir);
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        // 每次渲染必须reset相机位置, scale是缩放的比例
        float scale = 0.5;
        Utility::ResetCamera(Player->Position, glm::vec2(Width / 2.0f, Height / 2.0f), scale);
        // draw background
        Utility::DrawBackground();
        Player->Draw();

    }
}
