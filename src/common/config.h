#ifndef CONFIG_H
#define CONFIG_H
#include "../precomp.h"
//for Texture2D
#include "../util/Texture.h"

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <iostream>

#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

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
    GAME_CREDITS,
    GAME_LEVEL_UP,
    GAME_RESULT

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

class Item
{
public:
    int itemID;
    int level=0;//0级表示未持有
    std::shared_ptr<std::string> ItemName;
    static std::vector<std::vector<std::shared_ptr<std::string>>> itemIntroduction;//外层为id，内层为等级，储存了0~7级的文本的二维智能指针vector
    Item(int ID,std::shared_ptr<std::string> ItemName):itemID(ID),ItemName(ItemName){};
};


class WeaponItem:public Item
{
public:
    WeaponItem(int ID,std::shared_ptr<std::string> ItemName,float damage,float area,float speed,float amount,int pierece,float cool_down,int knock_back,float duration,std::shared_ptr<std::string> context)
    : Item(ID,ItemName),damage(damage),area(area),speed(speed),amount(amount),pierece(pierece),cool_down(cool_down),knock_back(knock_back),duration(duration),context(context){};
    float damage;//伤害
    float area;//攻击范围
    float speed;//弹道飞行速度
    float amount;//弹道发射数量
    int pierece;//穿透数目，-1表示可以任意穿透
    float cool_down;//冷却时间，单位为秒
    int knock_back;//击退距离
    float duration;//单次攻击持续时间，-1表示攻击持续固定时间
    std::shared_ptr<std::string> context;//说明文本
    void LevelUP()//升级时同时更新下一级的升级文本
    {
        if(itemID==0)//鞭子
        {
            if(level==1)
            {
                amount++;
            }else if(level==2)
            {
                damage+=5;
            }else if(level==3)
            {
                area*=1.1;
                damage+=5;
            }else if(level==4)
            {
                damage+=5;
            }else if(level==5)
            {
                area*=1.1;
                damage+=5;
            }else if(level==6)
            {
                damage+=5;
            }else if(level==7)
            {
                damage+=5;
            }
        }else if(itemID==1)//魔杖
        {
            if(level==1)
            {
                amount++;
            }else if(level==2)
            {
                cool_down-=0.2;
            }else if(level==3)
            {
                amount++;
            }else if(level==4)
            {
                damage+=10;
            }else if(level==5)
            {
                amount++;
            }else if(level==6)
            {
                pierece++;
            }else if(level==7)
            {
                damage+=10;
            }
        }else if(itemID==2)//小刀
        {
            if(level==1)
            {
                amount++;
            }else if(level==2)
            {
                amount++;
                damage+=5;
            }else if(level==3)
            {
                amount++;
            }else if(level==4)
            {
                pierece++;
            }else if(level==5)
            {
                amount++;
            }else if(level==6)
            {
                amount++;
                damage+=5;
            }else if(level==7)
            {
                pierece++;
            }
        }else if(itemID==3)//斧头
        {
            if(level==1)
            {
                amount++;
            }else if(level==2)
            {
                damage+=20;
            }else if(level==3)
            {
                pierece+=2;
            }else if(level==4)
            {
                amount++;
            }else if(level==5)
            {
                damage+=20;
            }else if(level==6)
            {
                pierece+=2;
            }else if(level==7)
            {
                damage+=20;
            }
        }else if(itemID==4)//十字架
        {
            if(level==1)
            {
                damage+=10;
            }else if(level==2)
            {
                area*=1.1;
                speed*=1.25;
            }else if(level==3)
            {
                amount++;
            }else if(level==4)
            {
                damage+=10;
            }else if(level==5)
            {
                area*=1.1;
                speed*=1.25;
            }else if(level==6)
            {
                amount++;
            }else if(level==7)
            {
                damage+=10;
            }
        }else if(itemID==5)//国王圣经
        {
            if(level==1)
            {
                amount++;
            }else if(level==2)
            {
                area*=1.25;
                speed*=1.3;
            }else if(level==3)
            {
                duration+=0.5;
                damage+=10;
            }else if(level==4)
            {
                amount++;
            }else if(level==5)
            {
                area*=1.25;
                speed*=1.3;
            }else if(level==6)
            {
                duration+=0.5;
                damage+=10;
            }else if(level==7)
            {
                amount++;
            }
        }else if(itemID==6)//火焰魔杖
        {
            if(level==1)
            {
                damage+=10;
            }else if(level==2)
            {
                damage+=10;
                speed*=1.2;
            }else if(level==3)
            {
                damage+=10;
            }else if(level==4)
            {
                damage+=10;
                speed*=1.2;
            }else if(level==5)
            {
                damage+=10;
            }else if(level==6)
            {
                damage+=10;
                speed*=1.2;
            }else if(level==7)
            {
                damage+=10;
            }
        }else if(itemID==7)//大蒜
        {
            if(level==1)
            {
                area*=1.4;
                damage+=2;
            }else if(level==2)
            {
                cool_down-=0.1;
                damage+=1;
            }else if(level==3)
            {
                area*=1.2;
                damage+=1;
            }else if(level==4)
            {
                cool_down-=0.1;
                damage+=2;
            }else if(level==5)
            {
                area*=1.2;
                damage+=1;
            }else if(level==6)
            {
                cool_down-=0.1;
                damage+=1;
            }else if(level==7)
            {
                area*=1.2;
                damage+=1;
            }
        }else if(itemID==8)//圣徒水
        {
            if(level==1)
            {
                amount++;
                area*=1.2;
            }else if(level==2)
            {
                duration+=0.5;
                damage+=10;
            }else if(level==3)
            {
                amount++;
                area*=1.2;
            }else if(level==4)
            {
                duration+=0.3;
                damage+=10;
            }else if(level==5)
            {
                amount++;
                area*=1.2;
            }else if(level==6)
            {
                duration+=0.3;
                damage+=5;
            }else if(level==7)
            {
                area*=1.2;
                damage+=5;
            }
        }else if(itemID==9)//卢恩石
        {
            if(level==1)
            {
                damage+=5;
                speed*=1.2;
            }else if(level==2)
            {
                duration+=0.3;
                damage+=5;
            }else if(level==3)
            {
                amount++;
            }else if(level==4)
            {
                damage+=5;
                speed*=1.2;
            }else if(level==5)
            {
                duration+=0.3;
                damage+=5;
            }else if(level==6)
            {
                amount++;
            }else if(level==7)
            {
                duration+=0.5;
            }
        }else if(itemID==10)//雷电指环
        {
            if(level==1)
            {
                amount++;
            }else if(level==2)
            {
                area*=2;
                damage+=10;
            }else if(level==3)
            {
                amount++;
            }else if(level==4)
            {
                area*=2;
                damage+=20;
            }else if(level==5)
            {
                amount++;
            }else if(level==6)
            {
                area*=2;
                damage+=20;
            }else if(level==7)
            {
                amount++;
            }
        }
        ++level;
        if(level<8) context=itemIntroduction[itemID][level];
    }
    void ShootBullet(std::vector<GameObject *>* bullets);
};

class PassiveItem:public Item
{
    //被动道具直接影响玩家的属性
    //故此处结构有待调整
public:
    //PassiveItem(play);
    PassiveItem(int ID,std::shared_ptr<std::string> ItemName):Item(ID,ItemName){};
};

class EnemyObject : public GameObject
{
public:
    float speed = 8;  // 怪物移动速度
    float power = 100;  // 怪物攻击力
    float health = 100; // 怪物当前血量
    //记录怪物重新被攻击的间隔
    int can_hit[6];//两次攻击之间的间隔帧
    int hit_count[6];//离受到下一次攻击还剩多少帧，为0时说明可以再一次受到攻击

    std::string sprite;
    // constructor(s)
    EnemyObject() = delete;
    EnemyObject(glm::vec2 pos, std::string sprite);
    // resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
    void Set_hit(std::shared_ptr<WeaponItem>* weapons);
    ~EnemyObject();
    void Move(glm::vec2 &dir);
    bool health_adjust(float health_damage);
};

class PickupObject : public GameObject
{
public:
    float speed = 60;
    std::string sprite;
    // constructor(s)
    PickupObject() = delete;
    PickupObject(glm::vec2 pos, std::string sprite);
    // resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
    ~PickupObject();
    void Move(glm::vec2 &dir);
};

class PlayerObject : public GameObject
{
public:
    WeaponObject* the_weapon;

    float might ; // 力量
    float speed;//飞行道具移动速度
    float move_speed;//人物移动速度
    float max_health;   // 最大生命
    float recovery;     // 生命恢复
    float current_health; // 当前生命
    float armor;//护甲
    float cooldown;//武器攻击间隔
    float area;//aoe武器攻击范围
    float duration;//武器持续攻击时间
    glm::vec2 magnet;//拾取距离
    float luck;//幸运值
    float growth;//经验获取提升
    int amount;//单次发射的武器投射物数目
    float exp;//当前经验值
    float next_exp;//下一级所需经验值
    int level;//等级

    int state;

    int weapon_count=0;
    int passive_count=0;
    std::shared_ptr<WeaponItem> WeaponPackage[6];
    std::shared_ptr<PassiveItem> PassivePackage[6];

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
    bool CheckColl(GameObject &other);
    void Attack(int frame_count,std::vector<GameObject *>* bullets);
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
    std::vector<std::shared_ptr<WeaponItem>> WeaponItemPool;
    std::vector<std::shared_ptr<PassiveItem>> PassiveItemPool;
    std::vector<EnemyObject *> Enemy;
    std::vector<PickupObject *> Exp;
    std::vector<GameObject *> Bullets[6];//六种武器的弹道
    //std::vector<std::shared_ptr<>>
    int frame_counter=0;//计时器，记录帧的变化
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
        for (auto it = Exp.begin(); it != Exp.end(); it++)
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

    void Render(bool have_texture = false);
    void Check_Hover_Press(float cursor_x, float cursor_y, bool button_left);

    void DrawButton(float cursor_x, float cursor_y, bool& button_left, bool have_texture = false);
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

    void Render(bool Is_Changed, int id);

};

class Voice
{
public:
    std::map<int, std::string> voices;
    std::map<int, PROCESS_INFORMATION> processes_sound;
    std::map<int, PROCESS_INFORMATION> processes_music;

    bool sound;
    bool music;
    bool vfx;
    bool vis;
    bool dam;

    Voice();
    ~Voice();
    void play(int id, int type);
    void stop_play(int id, int type);

};
//static Voice v;

#endif