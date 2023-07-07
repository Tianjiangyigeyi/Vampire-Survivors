#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "../precomp.h"
#include "../viewmodel/Utility.h"

#include "../viewmodel/GameObject.h"
#define INIT_DAMAGE_VELOCITY 2.00f
class PlayerObject : public GameObject
{
public:
    float DamageVelocity;
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