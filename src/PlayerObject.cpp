#include "PlayerObject.h"

PlayerObject::PlayerObject()
    : GameObject(), DamageVelocity(INIT_DAMAGE_VELOCITY), lv(1) {}

PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 size, unsigned int level, Texture2D sprite)
    : GameObject(pos, size, sprite), DamageVelocity(INIT_DAMAGE_VELOCITY * level), lv(level) {}


// resets the ball to initial Stuck Position (if ball is outside window bounds)
void PlayerObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->DamageVelocity = INIT_DAMAGE_VELOCITY;
    this->lv = 1;
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::Upgrade()
{
    ++lv;
    DamageVelocity = INIT_DAMAGE_VELOCITY * lv;
}