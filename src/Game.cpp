/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "learn-opengl/Game.h"

SpriteRenderer *Renderer;
GameObject *Player;
BallObject *Ball;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    // 加载着色器
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.fs", nullptr, "sprite");
    // 配置着色器
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
                                      static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // 设置专用于渲染的控制
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // 加载纹理
    ResourceManager::LoadTexture("objects/background.jpg", false, "background");
    ResourceManager::LoadTexture("objects/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("objects/block.png", false, "block");
    ResourceManager::LoadTexture("objects/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("objects/paddle.png", true, "paddle");
    // 加载关卡
    GameLevel one;
    one.Load("levels/one.lvl", this->Width, this->Height / 2);
    GameLevel two;
    two.Load("levels/two.lvl", this->Width, this->Height / 2);
    GameLevel three;
    three.Load("levels/three.lvl", this->Width, this->Height / 2);
    GameLevel four;
    four.Load("levels/four.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;
    // 加载挡板
    glm::vec2 playerPos = glm::vec2(
        this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
        this->Height - PLAYER_SIZE.y);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
    // 加载球
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
    Ball = new BallObject(ballPos, BALL_RADIUS, InitialVelocity(),
                          ResourceManager::GetTexture("face"));
    Balls.push_back(Ball);
}

glm::vec2 Game::InitialVelocity()
{
    glm::vec2 minDistance = glm::vec2(Width, Height);
    for (auto &box : Levels[Level].Bricks)
    {
        if (box.IsSolid || box.Destroyed) continue;
        glm::vec2 distance = glm::vec2(box.Position.x - Player->Position.x, box.Position.y - Player->Position.y);
        if (glm::length(distance) < glm::length(minDistance))
        {
            minDistance = distance;
        }
    }
    return glm::normalize(minDistance) * glm::length(RUNTIME_BALL_VELOCITY);
}

void Game::Update(float dt)
{
    for (auto &eachBall : Balls)
    {
        eachBall->Move(dt, this->Width);
        DoCollisions(eachBall);
    }
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
            if (Player->Position.x <= this->Width - Player->Size.x)
                dir.x += 1;
        }
        if (this->Keys[GLFW_KEY_W])
        {
            if (Player->Position.y >= this->Height - 10 * Player->Size.y)
                dir.y -= 1;
        }
        if (this->Keys[GLFW_KEY_S])
        {
            if (Player->Position.y <= this->Height - Player->Size.y)
                dir.y += 1;
        }
        if (dir != glm::vec2(0.0f, 0.0f))
        {
            Player->Position += glm::normalize(dir) * velocity;
            if (Ball->Stuck)
            {
                Ball->Position += glm::normalize(dir) * velocity;
            }
        }
        // unpin
        if (this->Keys[GLFW_KEY_SPACE])
        {
            Ball->Stuck = false;
            glm::vec2 ballPos = Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
            Ball = new BallObject(ballPos, BALL_RADIUS, InitialVelocity(),
                                  ResourceManager::GetTexture("face"));
            Balls.push_back(Ball);
        }
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        // draw background
        Renderer->DrawSprite(ResourceManager::GetTexture("background"),
                             glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
        // draw level
        this->Levels[this->Level].Draw(*Renderer);
        // draw paddle
        Player->Draw(*Renderer);
        // draw ball
        for (auto &eachBall : Balls)
        {
            eachBall->Draw(*Renderer);
        }
    }
}

void Game::DoCollisions(BallObject *thisBall)
{
    // with bricks
    bool AllKill = true;
    for (GameObject &box : this->Levels[this->Level].Bricks)
    {
        if (!box.Destroyed)
        {
            if (!box.IsSolid)
                AllKill = false;
            Collision collision = CheckCollision(*thisBall, box);
            if (std::get<0>(collision)) // if collision is true
            {
                // destroy block if not solid
                if (!box.IsSolid)
                    box.Destroyed = true;
                // collision resolution
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (dir == LEFT || dir == RIGHT) // horizontal collision
                {
                    thisBall->Velocity.x = -thisBall->Velocity.x; // reverse horizontal velocity
                    // relocate
                    float penetration = thisBall->Radius - std::abs(diff_vector.x);
                    if (dir == LEFT)
                        thisBall->Position.x += penetration; // move ball to right
                    else
                        thisBall->Position.x -= penetration; // move ball to left;
                }
                else // vertical collision
                {
                    thisBall->Velocity.y = -thisBall->Velocity.y; // reverse vertical velocity
                    // relocate
                    float penetration = thisBall->Radius - std::abs(diff_vector.y);
                    if (dir == UP)
                        thisBall->Position.y -= penetration; // move ball back up
                    else
                        thisBall->Position.y += penetration; // move ball back down
                }
            }
        }
    }
    if (AllKill)
    {
        // Next Level
        if (Level < this->Levels.size() - 1)
        {
            ++Level;
            ResetLevel();
        }
    }
    // with player
    Collision result = CheckCollision(*thisBall, *Player);
    if (!thisBall->Stuck && std::get<0>(result))
    {
        // check where it hit the board, and change velocity based on where it hit the board
        float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
        float distance = (thisBall->Position.x + thisBall->Radius) - centerBoard;
        float percentage = distance / (Player->Size.x / 2.0f);
        // then move accordingly
        float strength = 2.0f;
        glm::vec2 oldVelocity = thisBall->Velocity;
        thisBall->Velocity.x = RUNTIME_BALL_VELOCITY.x * percentage * strength;
        thisBall->Velocity.y = -1 * abs(thisBall->Velocity.y);
        thisBall->Velocity = glm::normalize(thisBall->Velocity) * glm::length(oldVelocity);
    }
}

Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),  // up
        glm::vec2(1.0f, 0.0f),  // right
        glm::vec2(0.0f, -1.0f), // down
        glm::vec2(-1.0f, 0.0f)  // left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}

Collision CheckCollision(BallObject &one, GameObject &two)
{
    // 获取圆的中心
    glm::vec2 center(one.Position + one.Radius);
    // 计算AABB的信息（中心、半边长）
    glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
    glm::vec2 aabb_center(
        two.Position.x + aabb_half_extents.x,
        two.Position.y + aabb_half_extents.y);
    // 获取两个中心的差矢量
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // AABB_center加上clamped这样就得到了碰撞箱上距离圆最近的点closest
    glm::vec2 closest = aabb_center + clamped;
    // 获得圆心center和最近点closest的矢量并判断是否 length <= radius
    difference = closest - center;
    if (glm::length(difference) <= one.Radius)
        return std::make_tuple(true, VectorDirection(difference), difference);
    else
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}

bool CheckCollision(GameObject &one, GameObject &two)
{
    return one.Position.x + one.Size.x >= two.Position.x && one.Position.x <= two.Position.x + two.Size.x && one.Position.y + one.Size.y >= two.Position.y && one.Position.y <= two.Position.y + two.Size.y;
}

void Game::ResetLevel()
{
    if (this->Level == 0)
        this->Levels[0].Load("levels/one.lvl", this->Width, this->Height * 0.5f);
    else if (this->Level == 1)
        this->Levels[1].Load("levels/two.lvl", this->Width, this->Height * 0.5f);
    else if (this->Level == 2)
        this->Levels[2].Load("levels/three.lvl", this->Width, this->Height * 0.5f);
    else if (this->Level == 3)
        this->Levels[3].Load("levels/four.lvl", this->Width, this->Height * 0.5f);
}

void Game::ResetPlayer()
{
    // Reset player/ball stats
    Player->Size = PLAYER_SIZE;
    Player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
    Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), InitialVelocity());
}