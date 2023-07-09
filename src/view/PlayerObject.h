#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "../precomp.h"
#include "../viewmodel/Utility.h"

#include "../viewmodel/GameObject.h"
#define INIT_DAMAGE_VELOCITY 2.00f
class PlayerObject : public GameObject
{
public:
    float might;//力量
    float speed;//飞行道具移动速度
    float move_speed;//人物移动速度
    float max_health;//最大生命
    float recovery;//生命恢复
    float current_health;//当前生命
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
    Texture2D sprites[4];
    // constructor(s)
    PlayerObject() = delete;
    PlayerObject(glm::vec2 pos, glm::vec2 size, unsigned int level, Texture2D sprite);
    PlayerObject(glm::vec2 pos,  Texture2D sprite1, Texture2D sprite2, Texture2D sprite3, Texture2D sprite4);
    // resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
    void Upgrade();
    ~PlayerObject();
    void Move(glm::vec2 &dir);


};

#endif