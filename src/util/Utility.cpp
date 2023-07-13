#include "Utility.h"
#include <iostream>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
std::vector<std::vector<std::shared_ptr<std::string>>> Item::itemIntroduction;
SpriteRenderer *Utility::Renderer;
void Utility::Init(std::shared_ptr<Game> game)
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
    ResourceManager::LoadTexture("assets/background/forest/dummy1.png", true, "background", WINDOW_WIDTH*4.0, WINDOW_HEIGHT*4.0);
    ResourceManager::LoadTexture("assets/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("assets/Enemies/Sprite-BAT1.png", true, "enemy");
    ResourceManager::LoadTexture("assets/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("assets/Player/Antonio/Animated-Antonio1.png", true, "player1");
    ResourceManager::LoadTexture("assets/Player/Antonio/Animated-Antonio2.png", true, "player2");
    ResourceManager::LoadTexture("assets/Player/Antonio/Animated-Antonio3.png", true, "player3");
    ResourceManager::LoadTexture("assets/Player/Antonio/Animated-Antonio4.png", true, "player4");
    ResourceManager::LoadTexture("assets/background/Start_Menu_bck.png", true, "StartMenu", WINDOW_WIDTH, WINDOW_HEIGHT);
    // ResourceManager::LoadTexture("assets/buttons/StartM_start_normal.jpg", false, "StartM_start_normal", WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.1);
    ResourceManager::LoadTexture("assets/Weapon trajectory/Sprite-Whip_tra0.png", true, "Weapon_tra0");
    ResourceManager::LoadTexture("assets/Weapon trajectory/Sprite-Whip_tra1.png", true, "Weapon_tra1");
    ResourceManager::LoadTexture("assets/Pickups/Sprite-Experience_Gem.png", true, "Experience");

    ResourceManager::LoadTexture("assets/Menu/confirm.png", true, "Confirm_button");
    ResourceManager::LoadTexture("assets/Menu/Antonio.png", true, "Sel_Antonio");
    ResourceManager::LoadTexture("assets/Menu/Arca.png", true, "Sel_Arca");

    ResourceManager::LoadTexture("assets/buttons/1-1.jpg", false, "1-1", WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.12);
    ResourceManager::LoadTexture("assets/buttons/1-2.png", false, "1-2", WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.12);
    ResourceManager::LoadTexture("assets/buttons/1-3.png", false, "1-3", WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.12);

    ResourceManager::LoadTexture("assets/background/2-2.png", false, "2-2", WINDOW_WIDTH*0.5, WINDOW_HEIGHT*0.8);

    char load_path[18]="assets/Font/0.png";
    load_path[17]='\0';
    char temp[3];
    temp[2]='\0';
    for(int i=0;i<10;i++)
    {
        load_path[12]=i+'0';
        temp[0]=i+'0';
        temp[1]='\0';
        ResourceManager::LoadTexture(load_path, true, temp);
    }
    for(int i=0;i<26;i++)
    {
        load_path[12]=i+'A';
        temp[0]=i+'A';
        temp[1]='\0';
        ResourceManager::LoadTexture(load_path, true, temp);
    }
    ResourceManager::LoadTexture("assets/Font/space.png", true, "space");
    ResourceManager::LoadTexture("assets/Font/,.png", true, ",");
    char load_path1[19]="assets/Font/a1.png";
    load_path1[18]='\0';
    for(int i=0;i<26;i++)
    {
        load_path[12]=i+'a';
        temp[0]=i+'a';
        temp[1]='\0';
        ResourceManager::LoadTexture(load_path, true, temp);
    }
    ////////////////////////////////////////////////////////////////////////
    game->BG_Height = ResourceManager::GetTexture("background").Height;
    
    game->BG_Width = ResourceManager::GetTexture("background").Width;
    //std::cout << BG_Height <<  "  " << BG_Width << std::endl;
    glm::vec2 playerPos = glm::vec2(
        game->BG_Width / 2.0f, game->BG_Height / 2.0f);
    game->Player = new PlayerObject(playerPos, "player4", "player1", "player2", "player3");
    game->Player->InitWeapon("Weapon_tra0", "Weapon_tra1");
    srand(time(NULL));
    //初始化文本属性

    std::vector<std::shared_ptr<std::string>> temp_vector;
    temp_vector.push_back(std::make_shared<std::string>("Attacks horizontally, passes through enemies."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 5."));
    temp_vector.push_back(std::make_shared<std::string>("Base Area up by 10%. Base Damage up by 5."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 5."));
    temp_vector.push_back(std::make_shared<std::string>("Base Area up by 10%. Base Damage up by 5."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 5."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 5."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Fires at the nearest enemy."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Cooldown reduced by 0.2 seconds."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 10."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Passes through 1 more enemy."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 10."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Fires quickly in the faced direction."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile. Base Damage up by 5."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Passes through 1 more enemy."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile. Base Damage up by 5."));
    temp_vector.push_back(std::make_shared<std::string>("Passes through 1 more enemy."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("High damage, high Area scaling."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 20."));
    temp_vector.push_back(std::make_shared<std::string>("Passes through 2 more enemies."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 20."));
    temp_vector.push_back(std::make_shared<std::string>("Passes through 2 more enemies."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 20."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Aims at nearest enemy, has boomerang effect."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 10."));
    temp_vector.push_back(std::make_shared<std::string>("Base Area up by 10%. Base Speed up by 25%."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 10."));
    temp_vector.push_back(std::make_shared<std::string>("Base Area up by 10%. Base Speed up by 25%."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 10."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Orbits around the character."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Base Area up by 25%. Base Speed up by 30%."));
    temp_vector.push_back(std::make_shared<std::string>("Effect lasts 0.5 seconds longer. Base Damage up by 10."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Base Area up by 25%. Base Speed up by 30%."));
    temp_vector.push_back(std::make_shared<std::string>("Effect lasts 0.5 seconds longer. Base Damage up by 10."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Fires at a random enemy, deals heavy damage."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 10."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 10. Base Speed up by 20%."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 10."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 10. Base Speed up by 20%."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 10."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 10. Base Speed up by 20%."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 10."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Damages nearby enemies. Reduces resistance to knockback and freeze."));
    temp_vector.push_back(std::make_shared<std::string>("Base Area up by 40%. Base Damage up by 2."));
    temp_vector.push_back(std::make_shared<std::string>("Cooldown reduced by 0.1 seconds. Base Damage up by 1."));
    temp_vector.push_back(std::make_shared<std::string>("Base Area up by 20%. Base Damage up by 1."));
    temp_vector.push_back(std::make_shared<std::string>("Cooldown reduced by 0.1 seconds. Base Damage up by 2."));
    temp_vector.push_back(std::make_shared<std::string>("Base Area up by 20%. Base Damage up by 1."));
    temp_vector.push_back(std::make_shared<std::string>("Cooldown reduced by 0.1 seconds. Base Damage up by 1."));
    temp_vector.push_back(std::make_shared<std::string>("Base Area up by 20%. Base Damage up by 1."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Generates damaging zones."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile. Base Area up by 20%."));
    temp_vector.push_back(std::make_shared<std::string>("Effect lasts 0.5 seconds longer. Base Damage up by 10."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile. Base Area up by 20%."));
    temp_vector.push_back(std::make_shared<std::string>("Effect lasts 0.3 seconds longer. Base Damage up by 10."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile. Base Area up by 20%."));
    temp_vector.push_back(std::make_shared<std::string>("Effect lasts 0.3 seconds longer. Base Damage up by 5."));
    temp_vector.push_back(std::make_shared<std::string>("Base Area up by 20%. Base Damage up by 5."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Passes through enemies, bounces around."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 5. Base Speed up by 20%."));
    temp_vector.push_back(std::make_shared<std::string>("Effect lasts 0.3 seconds longer. Base Damage up by 5."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Base Damage up by 5. Base Speed up by 20%."));
    temp_vector.push_back(std::make_shared<std::string>("Effect lasts 0.3 seconds longer. Base Damage up by 5."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Effect lasts 0.5 seconds longer."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Strikes at random enemies."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Base Area up by 100%. Base Damage up by 10."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Base Area up by 100%. Base Damage up by 20."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    temp_vector.push_back(std::make_shared<std::string>("Base Area up by 100%. Base Damage up by 20."));
    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Base damage up by 10%"));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Reduces incoming damage by 1."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Max health increases by 20%"));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Health recovery increases by 0.2 HP per second."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Cooldown reduced by 8.0%"));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Base area up by 10%"));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Base speed up by 10%"));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Effect lasts 10% longer"));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Fires 1 more projectile."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("Movement speed increases by 10%"));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    temp_vector.push_back(std::make_shared<std::string>("XP gain increases by 8%."));
    Item::itemIntroduction.push_back(temp_vector);
    temp_vector.clear();

    std::shared_ptr<WeaponItem> weapon_item=std::make_shared<WeaponItem>(0,std::make_shared<std::string>("Whip"),10,1,1,1,-1,1.35,1,-1,Item::itemIntroduction[0][0]);
    game->WeaponItemPool.push_back(weapon_item);
    weapon_item=std::make_shared<WeaponItem>(1,std::make_shared<std::string>("Magic Wand"),10,1,1,1,1,1.2,1,-1,Item::itemIntroduction[1][0]);
    game->WeaponItemPool.push_back(weapon_item);
    weapon_item=std::make_shared<WeaponItem>(2,std::make_shared<std::string>("Knife"),6.5,1,1,1,1,1.0f,0.5,-1,Item::itemIntroduction[2][0]);
    game->WeaponItemPool.push_back(weapon_item);
    weapon_item=std::make_shared<WeaponItem>(3,std::make_shared<std::string>("Axe"),20,1,1,1,3,4,1,2,Item::itemIntroduction[3][0]);
    game->WeaponItemPool.push_back(weapon_item);
    weapon_item=std::make_shared<WeaponItem>(4,std::make_shared<std::string>("Cross"),5,1,1,1,1,2,1,-1,Item::itemIntroduction[4][0]);
    game->WeaponItemPool.push_back(weapon_item);
    weapon_item=std::make_shared<WeaponItem>(5,std::make_shared<std::string>("King Bible"),10,1,1,1,1,3,1,3,Item::itemIntroduction[5][0]);
    game->WeaponItemPool.push_back(weapon_item);
    weapon_item=std::make_shared<WeaponItem>(6,std::make_shared<std::string>("Fire Wand"),20,1,0.75,3,1,3,1,-1,Item::itemIntroduction[6][0]);
    game->WeaponItemPool.push_back(weapon_item);
    weapon_item=std::make_shared<WeaponItem>(7,std::make_shared<std::string>("Garlic"),5,1,1,1,1,1.3,1,-1,Item::itemIntroduction[7][0]);
    game->WeaponItemPool.push_back(weapon_item);
    weapon_item=std::make_shared<WeaponItem>(8,std::make_shared<std::string>("Santa Water"),10,1,1,1,1,4.5,1,2,Item::itemIntroduction[8][0]);
    game->WeaponItemPool.push_back(weapon_item);
    weapon_item=std::make_shared<WeaponItem>(9,std::make_shared<std::string>("Runetracer"),10,1,1,1,1,3,1,2.25,Item::itemIntroduction[9][0]);
    game->WeaponItemPool.push_back(weapon_item);
    weapon_item=std::make_shared<WeaponItem>(10,std::make_shared<std::string>("Lightning Ring"),15,1,1,2,1,4.5,1,-1,Item::itemIntroduction[10][0]);
    game->WeaponItemPool.push_back(weapon_item);

}

void Utility::DrawBackground()
{
    auto tmp = ResourceManager::GetTexture("background");
    Renderer->DrawSprite(tmp, glm::vec2(0, 0), glm::vec2(tmp.Width,tmp.Height), 0.0f);
}

void Utility::DrawBackground(const std::string& background, glm::vec2 pos)
{
    auto tmp = ResourceManager::GetTexture(background);
    Renderer->DrawSprite(tmp, pos, glm::vec2(tmp.Width,tmp.Height), 0.0f);
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

void Utility::DestroyRenderer()
{
    delete Renderer;
}

void Utility::generateBackgroundColorTexture(int x, int y, unsigned int width, unsigned int height, float r, float g, float b, bool should_gen)
{
    // 创建Texture2D对象
    static Texture2D texture;
    if(should_gen) {
    texture.Width = width;
    texture.Height = height;
    texture.Internal_Format = GL_RGB;
    texture.Image_Format = GL_RGB;
    texture.Wrap_S = GL_REPEAT;
    texture.Wrap_T = GL_REPEAT;
    texture.Filter_Min = GL_LINEAR;
    texture.Filter_Max = GL_LINEAR;
    
    glGenTextures(1, &texture.ID);
    
    // 创建纯色背景像素数据
    unsigned char* pixels = new unsigned char[width * height * 3];
    for (unsigned int i = 0; i < width * height; ++i)
    {
        pixels[i * 3] = static_cast<unsigned char>(r * 255);
        pixels[i * 3 + 1] = static_cast<unsigned char>(g * 255);
        pixels[i * 3 + 2] = static_cast<unsigned char>(b * 255);
    }
    
    // 生成纹理
    glBindTexture(GL_TEXTURE_2D, texture.ID);
    glTexImage2D(GL_TEXTURE_2D, 0, texture.Internal_Format, width, height, 0, texture.Image_Format, GL_UNSIGNED_BYTE, pixels);
    
    // 设置纹理参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture.Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture.Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture.Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture.Filter_Max);
    
    // 解绑纹理对象
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // 释放像素数据
    delete[] pixels;
    }
    Renderer->DrawSprite(texture, glm::vec2(x, y), glm::vec2(width, height), 0.0f, glm::vec3(r, g, b), false);
}

void Utility::ClearBckGnd(std::string Bck_gnd)
{
    Utility::ResetCamera(glm::vec2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f), glm::vec2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f), 1.0f);
    Utility::DrawBackground(Bck_gnd);
}