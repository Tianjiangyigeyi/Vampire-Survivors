#ifndef MONSTEROBJECT_H
#define MONSTEROBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#define INIT_DAMAGE_VELOCITY_MONSTER 0.2f
class MonsterObject : public GameObject
{
public:
    float DamageVelocity;
    glm::vec2 direction = glm::vec2(0.0f, 0.0f);
    // constructor(s)
    MonsterObject();
    MonsterObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));
    // resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
    void Move();
    ~MonsterObject();
};

#endif