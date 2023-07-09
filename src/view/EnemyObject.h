#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "../precomp.h"
#include "../viewmodel/Utility.h"

#include "../viewmodel/GameObject.h"
#define INIT_DAMAGE_VELOCITY 2.00f
class EnemyObject : public GameObject
{
public:
    float speed;//怪物移动速度
    float power;//怪物攻击力
    float health;//怪物当前血量
    Texture2D sprite;
    // constructor(s)
    EnemyObject() = delete;
    EnemyObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite);
    // resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
    ~EnemyObject();
    void Move(glm::vec2 &dir);

};

#endif