#include "EnemyObject.h"

EnemyObject::EnemyObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
        : GameObject(pos,  sprite)
{
}


// resets the ball to initial Stuck Position (if ball is outside window bounds)
void EnemyObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
}

EnemyObject::~EnemyObject()
{
}

void EnemyObject::Move(glm::vec2 &dir)
{
    Position += dir;
    IsMirrored = dir.x < 0 ? true : false;
}
