#include "MonsterObject.h"

MonsterObject::MonsterObject()
    : GameObject(), DamageVelocity(INIT_DAMAGE_VELOCITY_MONSTER) {}

MonsterObject::MonsterObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color)
    : GameObject(pos, size, sprite, color, glm::vec2{{(0.2F)}, {(0.2F)}}), DamageVelocity(INIT_DAMAGE_VELOCITY_MONSTER) {}


// resets the ball to initial Stuck Position (if ball is outside window bounds)
void MonsterObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->DamageVelocity = INIT_DAMAGE_VELOCITY_MONSTER;
}

MonsterObject::~MonsterObject()
{
}

void MonsterObject::Move()
{
    this->Position += this->Velocity * this->direction;
}
