#ifndef WEAPONOBJECT_H
#define WEAPONOBJECT_H


#include "../precomp.h"
#include "../viewmodel/Utility.h"
#include "../viewmodel/GameObject.h"

#define MAX_LEVEL 8

class WeaponObject : public GameObject
{
public:
    int level;      //等级
    float rarity;   //稀有度
    float base_damage;  //基础伤害
    float area;     //攻击范围
    float speed;    //移动速度
    float amount;   //同时出现的数量
    float duration; //持续时间
    bool pierce;   //耐久，即最多对几个目标造成伤害
    float cooldown; //冷却时间
    bool block_by_wall;     //攻击是否会被不可破坏物阻挡

    Texture2D sprite;
    // constructor(s)
    WeaponObject() = delete;
    WeaponObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite);
    // resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
    ~WeaponObject();
    void Move(glm::vec2 &dir);

};


#endif
