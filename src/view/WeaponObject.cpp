#include "WeaponObject.h"


WeaponObject::WeaponObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
        : GameObject(pos,  sprite)
{
}


// resets the ball to initial Stuck Position (if ball is outside window bounds)
void WeaponObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
}

WeaponObject::~WeaponObject()
{
}