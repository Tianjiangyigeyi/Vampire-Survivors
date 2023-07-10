#include "Game.h"
#include "Button.h"
#include <vector>
#include <iostream>
#include <unistd.h>
#include <ctime>
#include <cstdlib>

extern double cursor_x, cursor_y;
extern bool LeftButtonPressed;

PlayerObject *Player;
std::vector<EnemyObject *> Enemy;

float deltaTime = 0;
int Ecount;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_START_MENU), Keys(), Width(width), Height(height), Button_left(false)
{
}

Game::~Game()
{
    delete Utility::GetRenderer();
    delete Player;
    for(auto it = Enemy.begin(); it!=Enemy.end(); it++){
        delete *it;
    }
}

void Game::Init()
{
    Utility::Init();
    BG_Height = ResourceManager::GetTexture("background").Height;
    
    BG_Width = ResourceManager::GetTexture("background").Width;
    //std::cout << BG_Height <<  "  " << BG_Width << std::endl;
    glm::vec2 playerPos = glm::vec2(
        this->BG_Width / 2.0f, this->BG_Height / 2.0f);
    Player = new PlayerObject(playerPos, ResourceManager::GetTexture("player4"), ResourceManager::GetTexture("player1"), ResourceManager::GetTexture("player2"), ResourceManager::GetTexture("player3"));
    srand(time(NULL));
//    glm::vec2 enemyPos = glm::vec2(0, 0);
//    Enemy = new EnemyObject(enemyPos, ResourceManager::GetTexture("enemy"));
}



void Game::Update(float dt)
{
    Ecount++;
    if(Ecount >= 90){
        Ecount = 0;
        glm::vec2 enemyPos, dir;
        unsigned int len = rand() % (this->Height*2 + this->Width*2);

        Texture2D the_enemy = ResourceManager::GetTexture("enemy");

        if(len<this->Height){
            dir = glm::vec2(this->Width + the_enemy.Width, len*2.0-this->Height);
            dir.x = - dir.x;
        }

        else if(len<this->Height+this->Width){
            dir = glm::vec2(len*2.0-this->Height*2.0-this->Width, this->Height + the_enemy.Height);
            dir.y = -dir.y;
        }

        else if(len<2*this->Height+this->Width)
            dir = glm::vec2(this->Width, len*2.0-this->Height*3.0-this->Width*2.0);
            
        else
            dir = glm::vec2(len*2.0-this->Height*4.0-this->Width*3, this->Height);

        enemyPos = Player->Position+dir;
        EnemyObject * temp = new EnemyObject(enemyPos, the_enemy);
        Enemy.push_back(temp);

        for(auto it = Enemy.begin(); it!=Enemy.end(); it++){
            glm::vec2 dir1 = glm::vec2( Player->Position.x - (*it)->Position.x, Player->Position.y - (*it)->Position.y);
            dir1 = glm::normalize(dir1);
            (*it)->Move(dir1);
        }
    }


    // for(auto it = Enemy.begin(); it!=Enemy.end(); it++){
    //     glm::vec2 dir1 = glm::vec2( Player->Position.x - (*it)->Position.x, Player->Position.y - (*it)->Position.y);
    //     dir1 = glm::normalize(dir1);
    //     (*it)->Move(dir1);
    // }
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
            if (Player->Position.x <= this->BG_Width-Player->Sprite.Width)
                dir.x += 1;
        }
        if (this->Keys[GLFW_KEY_W])
        {
            if (Player->Position.y >= 0.0f)
                dir.y -= 1;
        }
        if (this->Keys[GLFW_KEY_S])
        {
            if (Player->Position.y <= this->BG_Height-Player->Sprite.Height)
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
        for(auto it= Enemy.begin(); it!=Enemy.end(); it++)  (*it)->Draw();
    }
    if(this->State == GAME_START_MENU)
    {
        Utility::ResetCamera(glm::vec2(Width / 2.0f, Height / 2.0f), glm::vec2(Width / 2.0f, Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("StartMenu"));

 
        Button start_button(Width * 0.45, Height * 0.9, Width * 0.1, Height * 0.05, std::string("StartM    start"));
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
