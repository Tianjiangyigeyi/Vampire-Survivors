#include "Utility.h"
#include <iostream>
SpriteRenderer *Utility::Renderer;
void Utility::Init()
{
    // 加载着色器
    ResourceManager::LoadShader("assets/shaders/sprite.vs", "assets/shaders/sprite.fs", nullptr, "sprite");
    // 配置着色器
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH),
                                      static_cast<float>(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // 设置专用于渲染的控制
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    ResourceManager::LoadTexture("assets/background/forest/dummy1.png", true, "background");
    ResourceManager::LoadTexture("assets/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("assets/Enemies/Sprite-BAT1.png", true, "monster");
    ResourceManager::LoadTexture("assets/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("assets/Player/Antonio/Animated-Antonio1.png", true, "player1");
    ResourceManager::LoadTexture("assets/Player/Antonio/Animated-Antonio2.png", true, "player2");
    ResourceManager::LoadTexture("assets/Player/Antonio/Animated-Antonio3.png", true, "player3");
    ResourceManager::LoadTexture("assets/Player/Antonio/Animated-Antonio4.png", true, "player4");
    ResourceManager::LoadTexture("assets/background/Start_Menu_bck.png", true, "StartMenu", WINDOW_WIDTH, WINDOW_HEIGHT);
    ResourceManager::LoadTexture("assets/buttons/StartM_start_normal.jpg", true, "StartM_start_normal", WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.1);
    
}

void Utility::DrawBackground()
{
    auto tmp = ResourceManager::GetTexture("background");
    Renderer->DrawSprite(tmp, glm::vec2(0, 0), glm::vec2(tmp.Width,tmp.Height), 0.0f);
}

void Utility::DrawBackground(const std::string& background)
{
    auto tmp = ResourceManager::GetTexture(background);
    Renderer->DrawSprite(tmp, glm::vec2(0, 0), glm::vec2(tmp.Width,tmp.Height), 0.0f);
}

SpriteRenderer *&Utility::GetRenderer()
{
    return Renderer;
}

void Utility::ResetCamera(glm::vec2 pos, glm::vec2 center, float scale)
{
    float left, right, bottom, top;
    left = pos.x - center.x;
    right = center.x + pos.x;
    bottom = center.y + pos.y;
    top = pos.y - center.y;
    // std::cout << left << " " << right << " " << bottom << " " << top << std::endl;
    float factorX = (right - left) / 2.0f * (1.0f - 1.0f / scale);
    float factorY = (bottom - top) / 2.0f * (1.0f - 1.0f / scale);
    glm::mat4 projection = glm::ortho(left + factorX, right - factorX, bottom - factorY, top + factorY, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
}