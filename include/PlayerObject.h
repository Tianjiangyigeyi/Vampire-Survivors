#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "Texture.h"
#define INIT_DAMAGE_VELOCITY 2.00f
class PlayerObject : public GameObject
{
public:
    float DamageVelocity;
    unsigned int lv;
    int state;
    Texture2D sprites[4];
    // constructor(s)
    PlayerObject();
    PlayerObject(glm::vec2 pos, glm::vec2 size, unsigned int level, Texture2D sprite);
    PlayerObject(glm::vec2 pos, glm::vec2 size, unsigned int level, Texture2D sprite1, Texture2D sprite2, Texture2D sprite3, Texture2D sprite4);
    // resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
    void Upgrade();
    ~PlayerObject();
    void Move(glm::vec2 &dir);
};

#endif