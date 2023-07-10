#ifndef CONFIG_H
#define CONFIG_H
#include "../precomp.h"
#include <vector>
#include <iostream>
// The Width of the screen
#define WINDOW_WIDTH 800
// The height of the screen
#define WINDOW_HEIGHT 600
// max fps
#define MAX_FRAME_PER_SECOND 30

// Represents the current state of the game
enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    GAME_START_MENU
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
    bool Destroyed;
    bool IsMirrored;
    glm::vec2 Position, Size;
    glm::vec3 Color;
    float Rotation;
    std::string Sprite;
    // constructor(s)
    GameObject() = delete;
    // 如果size不合适直接set
    GameObject(glm::vec2 pos, std::string sprite);
    // draw sprite
    virtual void Draw();
    virtual ~GameObject();
    void SetSize(glm::vec2 size);
    glm::vec2 &GetSize();
    void SetPosition(glm::vec2 pos);
    glm::vec2 &GetPosition();
    bool CheckCollision(GameObject &other);
};
class PlayerObject : public GameObject
{
public:
    float might;          // 力量
    float speed;          // 飞行道具移动速度
    float move_speed;     // 人物移动速度
    float max_health;     // 最大生命
    float recovery;       // 生命恢复
    float current_health; // 当前生命
    float armor;          // 护甲
    float cooldown;       // 武器攻击间隔
    float area;           // aoe武器攻击范围
    float duration;       // 武器持续攻击时间
    float magnet;         // 拾取距离
    float luck;           // 幸运值
    float growth;         // 经验获取提升
    int amount;           // 单次发射的武器投射物数目
    float exp;            // 当前经验值
    float next_exp;       // 下一级所需经验值
    int level;            // 等级

    int state;
    std::string sprites[4];
    // constructor(s)
    PlayerObject() = delete;
    PlayerObject(glm::vec2 pos, glm::vec2 size, unsigned int level, std::string sprite);
    PlayerObject(glm::vec2 pos, std::string sprite1, std::string sprite2, std::string sprite3, std::string sprite4);
    // resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
    void Upgrade();
    ~PlayerObject();
    void Move(glm::vec2 &dir);
};
class EnemyObject : public GameObject
{
public:
    float speed;  // 怪物移动速度
    float power;  // 怪物攻击力
    float health; // 怪物当前血量
    std::string sprite;
    // constructor(s)
    EnemyObject() = delete;
    EnemyObject(glm::vec2 pos, std::string sprite);
    // resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
    ~EnemyObject();
    void Move(glm::vec2 &dir);
};

class WeaponObject : public GameObject
{
public:
    int level;          // 等级
    float rarity;       // 稀有度
    float base_damage;  // 基础伤害
    float area;         // 攻击范围
    float speed;        // 移动速度
    float amount;       // 同时出现的数量
    float duration;     // 持续时间
    bool pierce;        // 耐久，即最多对几个目标造成伤害
    float cooldown;     // 冷却时间
    bool block_by_wall; // 攻击是否会被不可破坏物阻挡

    std::string sprite;
    // constructor(s)
    WeaponObject() = delete;
    WeaponObject(glm::vec2 pos, glm::vec2 size, std::string sprite);
    // resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
    ~WeaponObject();
    void Move(glm::vec2 &dir);
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

    void DrawButton(float cursor_x, float cursor_y, bool button_left);
};

#endif