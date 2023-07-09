#include "Game.h"
#include "Button.h"
#include <vector>
#include <iostream>
#include <unistd.h>

extern double cursor_x, cursor_y;
extern bool LeftButtonPressed;

PlayerObject *Player;

float deltaTime = 0;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_START_MENU), Keys(), Width(width), Height(height), Button_left(false)
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
        // std::cout<<Player->Position.x<<" "<<Player->Position.y<<std::endl;
        // std::cout<<Width<<" "<<Height<<std::endl;
        // draw background
        Utility::DrawBackground();
        Player->Draw();

    }
    if(this->State == GAME_START_MENU)
    {
        Utility::ResetCamera(glm::vec2(Width / 2.0f, Height / 2.0f), glm::vec2(Width / 2.0f, Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("StartMenu"));

 
        Button start_button(Width * 0.45, Height * 0.9, Width * 0.1, Height * 0.1, std::string("StartM_start"));
        start_button.DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        if(start_button.pressed)
        {
            this->State = GAME_ACTIVE;
        }
        
        // this->State = GAME_ACTIVE;
        // std::cout <<"here"<<cursor_x<<std::endl;
        // sleep(1);
    }
}
