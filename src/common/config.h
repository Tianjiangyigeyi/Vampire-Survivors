#ifndef CONFIG_H
#define CONFIG_H
#include "../precomp.h"
//for Texture2D
#include "../util/Texture.h"

#include <vector>
#include <string>
#include <map>
#include <iostream>
// The Width of the screen
#define WINDOW_WIDTH 1600
// The height of the screen
#define WINDOW_HEIGHT 800
// max fps
#define MAX_FRAME_PER_SECOND 30
// To be select in the select menu
#define MAX_INT 2147483647


class static_Player{
public:
    std::string name;
    float might;
    float max_health;
    float attack;
    float speed;
    float armor;

    static_Player(std::string name, float might, float max_health, float attack, float speed, float armor)
        : name(name), might(might), max_health(max_health), attack(attack), speed(speed), armor(armor){};
};


// Represents the current state of the game
enum GameState
{
    GAME_ACTIVE,
    GAME_PAUSE,
    GAME_MENU,
    GAME_WIN,
    GAME_OVER,
    GAME_START_MENU,
    GAME_SELECT_MENU,
    GAME_SETTING_MENU,
    GAME_PEOPLE_SELECT,
    GAME_WEAPON_SELECT,
    GAME_MAP_SELECT

};

const glm::vec2 PLAYER_SIZE(10.0f, 10.0f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(50.0f);
// Initial velocity of the Ball
// const glm::vec2 INITIAL_BALL_VELOCITY(0.0f, -350.0f);
const glm::vec2 RUNTIME_BALL_VELOCITY(10.0f, -35.f);
// Radius of the ball object
class GameObject
{
public:
    // object state
    bool IsSolid;
    int  Destroyed ;
    bool IsMirrored;
    glm::vec2 Position, Size, Coll_Size;
    glm::vec3 Color;
    float Rotation;
    std::string Sprite;
    // constructor(s)
    GameObject() = delete;
    // 如果size不合适直接set
    GameObject(glm::vec2 pos, std::string sprite);
    // draw sprite
    void Draw();
    void Draw( glm::vec3 color);
    virtual ~GameObject();
    void SetSize(glm::vec2 size);
    void SetColl_Size(glm::vec2 size);
    glm::vec2 &GetSize();
    void SetPosition(glm::vec2 pos);
    glm::vec2 &GetPosition();
    bool CheckCollision(GameObject &other);
};

class WeaponObject : public GameObject
{
public:
    int level;          // 等级
    float rarity;       // 稀有度
    float base_damage =  10;  // 基础伤害
    float area;         // 攻击范围
    float speed;        // 移动速度
    float amount;       // 同时出现的数量
    float duration;     // 持续时间
    bool pierce;        // 耐久，即最多对几个目标造成伤害
    float cooldown;     // 冷却时间
    bool block_by_wall; // 攻击是否会被不可破坏物阻挡

    int state;
    std::string sprites[2];
    // constructor(s)
    WeaponObject() = delete;
    //WeaponObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite);
    WeaponObject(glm::vec2 pos, std::string sprite0, std::string sprite1);
    // resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
    ~WeaponObject();
    void Move(glm::vec2 &dir);
};

class PlayerObject : public GameObject
{
public:
    WeaponObject* the_weapon;

    float might = 100; // 力量
    float speed;//飞行道具移动速度
    float move_speed;//人物移动速度
    float max_health;   // 最大生命
    float recovery;     // 生命恢复
    float current_health; // 当前生命
    float armor;//护甲
    float cooldown;//武器攻击间隔
    float area;//aoe武器攻击范围
    float duration;//武器持续攻击时间
    float magnet;//拾取距离
    float luck;//幸运值
    float growth;//经验获取提升
    int amount;//单次发射的武器投射物数目
    float exp;//当前经验值
    float next_exp;//下一级所需经验值
    int level;//等级

    int state;
    std::string sprites[4];
    // constructor(s)
    PlayerObject() = delete;
//    PlayerObject(glm::vec2 pos, glm::vec2 size, unsigned int level, std::string sprite);
    PlayerObject(glm::vec2 pos,  std::string sprite1, std::string sprite2, std::string sprite3, std::string sprite4);
    void InitWeapon(std::string Weapon_tra0, std::string Weapon_tra1);
    // resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
    void Upgrade();
    ~PlayerObject();
    void Move(glm::vec2 &dir);
    bool health_adjust(float health_damage);
};

class EnemyObject : public GameObject
{
public:
    float speed = 8;  // 怪物移动速度
    float power = 100;  // 怪物攻击力
    float health = 100; // 怪物当前血量
    std::string sprite;
    // constructor(s)
    EnemyObject() = delete;
    EnemyObject(glm::vec2 pos, std::string sprite);
    // resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
    ~EnemyObject();
    void Move(glm::vec2 &dir);
    bool health_adjust(float health_damage);
};

class Game
{
public:
    GameState State;
    bool Keys[1024];
    bool Button_left;
    unsigned int Width, Height;
    unsigned int BG_Width, BG_Height;
    unsigned int Level;
    PlayerObject *Player;
    std::vector<EnemyObject *> Enemy;

    // constructor/destructor
    Game(unsigned int width, unsigned int height)
            : State(GAME_START_MENU), Keys(), Width(width), Height(height), Button_left(false)
    {
    }

    ~Game()
    {
        delete Player->the_weapon;
        delete Player;
        for (auto it = Enemy.begin(); it != Enemy.end(); it++)
        {
            delete *it;
        }
    }

};

class Button
{
public:
    float x, y;
    float width, height;
    bool hovered;
    bool pressed;
    std::string Button_text;

    std::string normal_texture;
    std::string hovered_texture;
    std::string pressed_texture;

    Button(float x, float y, float width, float height, std::string button_text)
        : x(x), y(y), width(width), height(height), hovered(false), pressed(false), Button_text(button_text){};

    void Render();
    void Check_Hover_Press(float cursor_x, float cursor_y, bool button_left);

    void DrawButton(float cursor_x, float cursor_y, bool &button_left);
};

class TextBox
{
public:
    std::string text;
    std::string texture_text;
    float x,y;
    float width,height;
    Texture2D bckgrnd_texture;
    bool bckgrnd;
    glm::vec3 bckgrnd_color;

    TextBox(float x,float y,float width,float height,glm::vec3 color,std::string text)
        :x(x),y(y),width(width),height(height),bckgrnd_color(color), text(text) 
        {bckgrnd = true;};

    TextBox(float x,float y,float width,float height,std::string text, std::string texture_text)
        :x(x),y(y),width(width),height(height), text(text) , texture_text(texture_text)
        {bckgrnd = false;};

    void Render();
    void setText(std::string new_text);

    void DrawRect(float x, float y, float width, float height, float r, float g, float b);


};

class ValLine
{
public:
    int actual_length;
    int actual_height;
    int posx, posy;
    int val_left;
    int max_val;
    glm::vec3 color_left;
    glm::vec3 color_right;

    ValLine(int act_len, int act_hgt, int posx, int posy, int val_left, int max_val, glm::vec3 color_left, glm::vec3 color_right)
        : actual_length(act_len), actual_height(act_hgt), posx(posx), posy(posy), val_left(val_left), max_val(max_val), color_left(color_left), color_right(color_right){};

    void Render(bool Is_Changed);

};

#endif